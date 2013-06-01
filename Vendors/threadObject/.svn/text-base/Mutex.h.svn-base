/*
 * Mutex.h
 *
 *  Created on: 18/giu/2012
 *      Author: emanuele_galli
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Mutex {
public:
	friend class MutexCondition;
	Mutex();
	virtual ~Mutex();

	void Lock();
	void Unlock();

private :
    pthread_mutex_t _Mutex;		//## attribute _Mutex
};

#endif /* MUTEX_H_ */
