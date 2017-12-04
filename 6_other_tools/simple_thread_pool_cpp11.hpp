#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

namespace std
{
#define  MAX_THREAD_NUM 256
    // Class non-static member function is not included for Task type
    class threadpool
    {
        using Task = std::function<void()>;

        // Thread pool
        std::vector<std::thread> vec_pool;
        // Task queue waiting for running
        std::queue<Task> queue_task;
        // Mutex for sychronizing
        std::mutex m_lock;
        // Blocking condition variable
        std::condition_variable cv_task;
        // Is close submit
        std::atomic<bool> is_stop;
        // Idle thread number
        std::atomic<int>  n_idle_nb;

    public:
        inline threadpool(unsigned short size = 4) : is_stop { false }
        {
            n_idle_nb = size < 1 ? 1 : size;
            for (size = 0; size < n_idle_nb; ++size)
            {
                // Initalize thread count
                vec_pool.emplace_back(
                    [this]{
                        // Lambda working thread function
                        while (!this->is_stop)
                        {
                            std::function<void()> task;
                            {
                                // Comparing with 'lock_guard', 'unique_lock' can call 'lock()' or 'unlock()' at any time
                                std::unique_lock<std::mutex> lock{ this->m_lock };
                                this->cv_task.wait(lock,
                                    [this] {
                                        return this->is_stop.load() || !this->queue_task.empty();
                                    });
                                if (this->is_stop && this->queue_task.empty())
                                    return;
                                task = std::move(this->queue_task.front());
                                this->queue_task.pop();
                            }
                            n_idle_nb--;
                            task();
                            n_idle_nb++;
                        } // End of while loop
                    }); // End of lambda function
            } // End of for loop
        } // End of constructor

        threadpool(const threadpool&) = delete;
        threadpool operator=(const threadpool&) = delete;

        inline ~threadpool()
        {
            is_stop.store(true);
            // Invoking all thread
            cv_task.notify_all();
            for (std::thread& thread : vec_pool) {
                //thread.detach();   /* Detaching the thread, seems not to be a good idea. */
                if (thread.joinable())
                    thread.join();   /* Waiting until thread finish (well, what if it never finishes...) */
            }
        }

    public:
        template<class F, class... Args>
        auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
        {
            if (is_stop.load())
                throw std::runtime_error("commit on ThreadPool is stopped.");

            using ReturnType = decltype(f(args...));
            auto task = std::make_shared<std::packaged_task<ReturnType()> >(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...));
            std::future<ReturnType> future = task->get_future();
            {
                // Push task into queue
                std::lock_guard<std::mutex> lock{ m_lock };
                queue_task.emplace(
                    [task](){
                        (*task)();
                    });
            }
            cv_task.notify_one();

            return future;
        }

        int get_idle_count() { return n_idle_nb; }

    };
}

#endif
