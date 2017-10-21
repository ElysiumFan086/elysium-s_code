#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <stdlib.h>

template <typename T>
class Singleton
{
public:
    static T *get_instance()
    {
        if (0 == s_instance)
        {
            s_instance = new (T)();
            atexit(destory);
        }
        return s_instance;
    }

    Singleton()  { }
    ~Singleton() { }
    
private:
    static void destory()
    {
        delete s_instance;
        s_instance = 0;
    }
    
private:
    static T* volatile s_instance;
};

template <typename T>
T* volatile Singleton<T>::s_instance = 0;

#endif