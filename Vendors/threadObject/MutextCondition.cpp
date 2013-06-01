/*
 * MutextCondition.cpp
 *
 *  Created on: 18/giu/2012
 *      Author: emanuele_galli
 */

#include "MutextCondition.h"
#include "Mutex.h"

#include <iostream>
#include <assert.h>


MutexCondition::MutexCondition(Mutex *mutex) : pMutex(mutex){
	assert(pthread_cond_init(&_Condition, NULL) == 0);
}

MutexCondition::~MutexCondition() {
	if(pthread_cond_destroy(&_Condition) != 0)
		Signal();
	pthread_cond_destroy(&_Condition);
}

void MutexCondition::Signal(void* (*_funct_to_exec_before_signal)(void*), void *_funct_arg){
	pMutex->Lock();
	if(_funct_to_exec_before_signal)
		_funct_to_exec_before_signal(_funct_arg);
	if(pthread_cond_signal(&_Condition) != 0){
		std::cerr << "Error in pthread_cond_signal" << std::endl;
	}
	pMutex->Unlock();
}

void MutexCondition::Wait(void* (*_funct_to_exec_after_signal)(void*), void *_funct_arg){
	pMutex->Lock();
	if(pthread_cond_wait(&_Condition, &(pMutex->_Mutex)) != 0){
		std::cerr << "Error in pthread_cond_wait" << std::endl;
		pMutex->Unlock();
		return;
	}
	if(_funct_to_exec_after_signal)
		_funct_to_exec_after_signal(_funct_arg);
	pMutex->Unlock();
}


void MutexCondition::Signal(){
	Signal(NULL);
	std::cout << "Signal NULL" << std::endl;
}

void MutexCondition::Wait(){
	Wait(NULL);
	std::cout << "Wait NULL" << std::endl;
}

