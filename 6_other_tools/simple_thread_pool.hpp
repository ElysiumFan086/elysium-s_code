
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

template<class T>
class SynQueue {
public:
	SynQueue(int n_max_size) : m_max_size(n_max_size), m_need_stop(false) {}

	void put(const T& x) { add(x); }
	void put(T&& x) { add(std::forward<T>(x)); }

	void take(std::list<T>& list) {
		std::unique_lock<std::mutex> locker(m_mutex);
		m_not_empty.wait(locker, [this] { return m_need_stop || not_empty(); });

		if(m_need_stop)    return;
		list = std::move(m_queue);
		m_not_full.notify_one();
	}

	void take(T& t) {
		std::unique_lock<std::mutex> locker(m_mutex);
		m_not_empty.wait(locker, [this] {return m_need_stop || not_empty(); });

		if(m_need_stop)    return;
		t = m_queue.front();
		m_queue.pop_front();
		m_not_full.notify_one();
	}

	void stop() {
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_need_stop = true;
		}

		m_not_full.notify_all();
		m_not_empty.notify_all();
	}

	bool empty() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.empty();
	}

	bool full() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.size() == m_max_size;
	}

	std::size_t size() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.size();
	}

	int count() {
		return m_queue.size();
	}

private:
	bool not_full() const {
		bool is_full = m_queue.size() >= m_max_size;
		if(is_full)    std::cout << "Queue buffer is full, please wait..." << std::endl;
		return !is_full;
	}

	bool not_empty() const {
		bool is_empty = m_queue.empty();
		if(is_empty)    std::cout << "Queue buffer is empty..." << std::endl;
		return !is_empty;
	}

	template<typename F>
	void add(F&& x) {
		std::lock_guard<std::mutex> locker(m_mutex);
		m_not_full.wait(locker, [this] { return m_need_stop || not_full(); } );

		if(m_need_stop)    return;
		m_queue.push_back(std::forward<F>(x));
		m_not_empty.notify_one();
	}

private:
	std::list<T> m_queue;
	std::mutex   m_mutex;
	std::condition_variable m_not_empty;
	std::condition_variable m_not_full;

	int  n_max_size;
	bool m_need_stop;
};

#include <functional>
#include <memory>
#include <atomic>

const int MAX_TASK_COUNT = 100;

class ThreadPool {
public:
	using Task = std::funtion<void()>;

	ThreadPool(int n_num_thread = std::thread::hardware_concurrency()) : m_queue(MAX_TASK_COUNT) {
		start(n_num_thread);
	}

	~ThreadPool() { stop(); }

	void stop() {
		std::call_once(m_flag, [this] { stop_thread_group(); });
	}

	void add_task(Task&& task) {
		m_queue.put(std::forward<Task>(task));
	}

	void add_task(const Task& task) {
		m_queue.put(task);
	}

private:
	void start(int n_num_thread) {
		m_running = true;
		for(int i = 0; i < n_num_thread; ++i) {
			m_thread_group.push_back(std::make_shared<std::thread>(&ThreadPool::run_in_thread, this));
		}
	}

	void run_in_thread() {
		while(m_running) {
			std::list<Task> list;
			m_queue.take(list);

			for(auto& task : list) {
				if(!m_running)    return;

				task();
			}
		}
	}

	void stop_thread_group() {
		m_queue.stop();
		m_running = false;

		for(auto thread : m_thread_group) {
			if(thread)    thread->join();
		}

		m_thread_group.clear();
	}

	std::list<std::shared_ptr<std::thread>> m_thread_group;
	SynQueue<Task> m_queue;
	atomic_bool m_running;
	std::once_flag m_flag;
};
