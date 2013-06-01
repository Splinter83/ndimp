/*
 * Mutex.cpp
 *
 *  Created on: 18/giu/2012
 *  Author: Emanuele Galli
 */

#include "Mutex.h"

#include <assert.h>


Mutex::Mutex() {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&_Mutex,&attr);
}

Mutex::~Mutex() {
	pthread_mutex_unlock(&_Mutex);
	pthread_mutex_destroy(&_Mutex);
}

void Mutex::Lock(){
	assert(pthread_mutex_lock(&_Mutex) == 0);
}

void Mutex::Unlock(){
	assert (pthread_mutex_unlock(&_Mutex) == 0);
}

