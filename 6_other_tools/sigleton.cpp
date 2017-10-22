/**
   Singleton implement version 1.0
      This class does not take thread save into consideration, for if two thread invode 'get_instance()' 
   at the same time, at which time 'm_instance' is a NULL pointer, 'new' operator will be excuted twice. 
   Therefor, although each calling thread can get a instance, yet there exists really two instances in 
   memory, which is not allowed in singleton pattern.
      Function 'get_instance()' returning a reference instead of a pointer, pointer exposes to user may 
   lead to an unsafe situation, in which user can 'delete' Sigleton pointer.
 */
class Singleton
{
	public:
		static Singleton& get_instance()
		{
			if(m_instance == NULL)
				m_instance = new Singleton;
			return *m_instance;
		}

	private:
		Singleton() { }
		~Singleton() { }
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		static Singleton* m_instance;
};

Singleton* Singleton::m_instance = NULL;

/*********************************************************************************************************/

/**
   Singleton implement version 2.0
       This version uses a non-local static member in class Singleton, instead of a pointer initializing with 
    NULL. Such changing may have solved the problem in multi-thread calling, for static member is initialized  
    when compiling. However, 'm_instance' is a non-local static member, whose initializing order is undefined 
    in different complie units. If a thread calling 'get_instance' before initializing finishing, error will 
    surely occure.
 */
class Singleton
{
	public:
		static Singleton& get_instance()
		{
			return instance;
		}

	private:
		Singleton() { }
		~Singleton() { }
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		static Singleton m_instance;
};

Singleton Singleton::instance;

/**********************************************************************************************************/

/**
   Singleton implement version 3.0
       Following Scott Meyers' advice in 'Effective C++', we can make the singleton instance as a local-static 
   variable in 'get_instance()' function. The instance is firstly initialized when 'get_instance()' is invoked 
   first time.
 */

class Singleton
{
	public:
		static Singleton& get_instance()
		{
			static Singleton m_instance;
			return m_instance;
		}

	private:
		Singleton() { }
		~Singleton() { }
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;	
};

/**********************************************************************************************************/

/**
   Singleton implement version 1.1
      On the base of version 1.0, we can add lock with mutex to make instance creating code a critical section.
   If so, when a thread is creating an instance, another thread that attemps to do the same thing will be 
   blocked by mutex. In following code, 'Code A' and 'Code B' are asked to exist at the same time, you can think 
   it yourself what will happen without either of them.
 */

class Singleton
{
	public:
		static Singleton& get_instance()
		{
			if(m_instance == NULL)         // Code A
			{	
				std::lock_guard<std::mutex> lock(mtx_instance);
				if(m_instance == NULL)     // Code B
					m_instance = new Singleton;
			}
			return *m_instance;
		}	

	private:
		Singleton() { }
		~Singleton() { }
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		static Singleton* m_instance;

		std::mutex mtx_instance;
};

Singleton* Singleton::m_instance = NULL;

/**********************************************************************************************************/

/**
   Singleton implement version 4.0
      This version is coded with template, with which any class can derived from it to implement their own 
   Singleton version. Considering all versions mentioned above, this version may be not that safe in multi-
   thread environment, yet it just give us a new way to think how Singleton can be used in project codeing.

   Usage Example:

   class LogManager : public Singleton<LogManager>{
     ... ...
   	public:
   		void log_message(const std::string& str_msg, int n_type);

   	 ... ...
   };

   // Calling code
   LogManager::get_instance().log_message("Logging test", LOG_INFO);
 */

template <typename T>
class Singleton
{
public:
    static T& get_instance()
    {
        static T s_instance;
        return s_instance;
    }

private:
    Singleton()  { }
    ~Singleton() { }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};


void reverse(char* p_data, std::size_t n_len){
	std::size_t n_begin = 0;
	std::size_t n_end   = n_len;

	while(n_begin < n_end){
		p_data[n_begin] = (p_data[n_begin] ^ p_data[n_end]);
		p_data[n_end]   = (p_data[n_begin] ^ p_data[n_end]);
		p_data[n_begin] = (p_data[n_begin] ^ p_data[n_end]);
		n_begin++;
		n_end--;
	}
}

bool find_duplicate(int* p_num, int n_len, int* p_dup_num){
	if(p_num == NULL || n_len <= 0)  return false;
	for(int i = 0; i < n_len; ++i){
		if(p_num[i] < 0 || p_num[i] > n_len - 1)
			return false;
	}

	for(int i = 0; i < n_len; ++i){
		while(p_num[i] != i){
			if(p_num[i] == p_num[p_num[i]]){
				*p_dup_num = p_num[i];
				return true;
			}
			swap(p_num[i], p_num[p_num[i]]);
		}
	}
}

int count_range(const int* p_num, int n_len, int n_start, int n_end){
	if(p_num == NULL)  return 0;
	int n_count = 0;
	for(int i = 0; i < n_len; ++i){
		if(p_num[i] >= n_start && p_num[i] <= n_end)
			++n_count;
	}
	return n_count;
}

int find_duplicate(const int* p_num, int n_len){
	if(p_num == NULL || n_len <= 0)  return false;
	for(int i = 0; i < n_len; ++i){
		if(p_num[i] < 0 || p_num[i] > n_len - 1)
			return false;
	}

	int n_start = 1, n_end = n_len - 1;
	while(n_end >= n_start){
		int n_middle = n_start + ((n_end - n_start) >> 1);
		int n_count = count_range(p_num, n_len, n_start, n_middle);
		if(n_end = n_start){
			if(n_count > 1)
				return n_start;
			else
				break;
		}
		if(n_count > (n_middle - n_start + 1))
			n_end = n_middle;
		else
			n_start = n_middle + 1;
	}
	return -1;
}