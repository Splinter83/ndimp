/*
 * MutextCondition.h
 *
 *  Created on: 18/giu/2012
 *      Author: emanuele_galli
 */

#ifndef MUTEXTCONDITION_H_
#define MUTEXTCONDITION_H_

#include <memory>
#include <auto_ptr.h>
#include "Mutex.h"

class MutexCondition {
public:
	MutexCondition(Mutex*);
	virtual ~MutexCondition();

	void Signal(void* (*_funct_to_exec_before_signal)(void*), void *_funct_arg = NULL);
	void Wait(void* (*_funct_to_exec_after_signal)(void*), void *_funct_arg = NULL);

	void Signal();
	void Wait();
private:
	pthread_cond_t _Condition;
	Mutex *pMutex;
};

#endif /* MUTEXTCONDITION_H_ */
