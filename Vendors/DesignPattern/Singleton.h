/*
 * SimpStimpProject: Singleton.h
 *
 *  Created on: 01/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <pthread.h>

// Creation policies
template<class T> struct CreateNotThreadSafe
{
    static T* Create()
    {
        if(myClass == 0)
    	    return myClass = new T;
        return myClass;
    }
private:
    static T* myClass;
};
template<class T>
T* CreateNotThreadSafe<T>::myClass = 0;

// Creation policies
template<class T> struct CreateThreadSafe
{
public:
	static T* Create()
    {
    	if (myClass == 0) {
    		pthread_mutex_lock(&_mutex);
    		if (myClass == 0){
    			myClass = new T();
    			pthread_mutex_unlock(&_mutex);
    			return myClass;
    		}
    		else{
    			pthread_mutex_unlock(&_mutex);
    			return myClass;
    		}
    	}
    	return myClass;
    }
private:
    static T* myClass;
    static pthread_mutex_t _mutex;

};

template<class T>
pthread_mutex_t CreateThreadSafe<T>::_mutex = PTHREAD_MUTEX_INITIALIZER;

template<class T>
T* CreateThreadSafe<T>::myClass = 0;

// Singleton
template <class T, template<class> class CreationPolicy> class Singleton;

template <class T, template<class> class CreationPolicy>
class Singleton
{
public:
    static T* instance()
    {
        m_instance = CreationPolicy<T>::Create();
        return m_instance;
    }
private:
    Singleton& operator=(const Singleton&);
    static T* m_instance;
};

template <class T, template<class> class C>
T* Singleton<T, C>::m_instance = 0;

#if __GNUG__ >= 4 && (__GNUC_MINOR__ >= 6)

	template <class T, template<class> class CreationPolicy> class Singleton;
	#define SINGLETON_THREAD_SAFE friend class Singleton; \
	                          template <class T> friend class CreateThreadSafe;
	#define SINGLETON friend class Singleton; \
                  template <class T> friend class CreateNotThreadSafe;

#else
	#define SINGLETON_THREAD_SAFE template <class T, template<class> class CreationPolicy> friend class Singleton; \
	                          template <class T> friend class CreateThreadSafe;
	#define SINGLETON friend class <class T, template<class> class CreationPolicy> Singleton; \
                  template <class T> friend class CreateNotThreadSafe;
#endif

#endif /* SINGLETON_H_ */
