/*
 * Thread.cpp
 *
 *  Created on: 06/giu/2012
 *      Author: emanuele_galli
 */

#include "Thread.h"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Runnable::~Runnable() {
} // a function body is required for pure virtual destructors


void Runnable::Sleep(unsigned int usleep){
	struct timespec sleepTime;
	struct timespec remainingSleepTime;

	sleepTime.tv_sec = usleep / ((unsigned int)1e6);
	sleepTime.tv_nsec= (usleep - (unsigned int)(sleepTime.tv_sec * 1e6)) * 1000;

	nanosleep(&sleepTime,&remainingSleepTime);
}

Thread::Thread(auto_ptr<Runnable> runnable_, bool isDetached) :
		runnable(runnable_), detached(isDetached) {
	if (runnable.get() == NULL) {
		std::cout
				<< "Thread::Thread(auto_ptr<Runnable> runnable_, bool isDetached) failed at "
				//<< '' << __FILE__ << ":" << __LINE__ << " - "
				<< " runnable is NULL " << std::endl;
		exit(-1);
	}
	std::cout << "Runnable found" << std::endl;
}

Thread::Thread(bool isDetached) :
		runnable(NULL), detached(isDetached) {
}

void* Thread::startThreadRunnable(void* pVoid) {
// thread start function when a Runnable is involved
	Thread* runnableThread = static_cast<Thread*>(pVoid);
	assert(runnableThread);
	runnableThread->result = runnableThread->runnable->run();
	runnableThread->setCompleted();
	return runnableThread->result;
}

void* Thread::startThread(void* pVoid) {
// thread start function when no Runnable is involved
	Thread* aThread = static_cast<Thread*>(pVoid);
	assert(aThread);
	aThread->result = aThread->run();
	aThread->setCompleted();
	return aThread->result;
}

Thread::~Thread() {
}

void* Thread::join() {
	int status = pthread_join(PthreadThreadID, NULL);
// result was already saved by thread start functions
	if (status != 0) {
		perror("Error in Thread join");
		exit(status);
	}

	return NULL;
}

void Thread::setCompleted() {
	/* completion was handled by pthread_join() */
}

void Thread::start() {
	int status = pthread_attr_init(&threadAttribute); // initialize attribute object
	if (status != 0) {
		perror("pthread_attr_init error");
		exit(status);
	}
	status = pthread_attr_setscope(&threadAttribute, PTHREAD_SCOPE_SYSTEM);
	if (status != 0) {
		perror("pthread_attr_setscope error");
		exit(status);
	}
	if (!detached) {
		if (runnable.get() == NULL) {
			int status = pthread_create(&PthreadThreadID, &threadAttribute,
					Thread::startThread, (void*) this);
			if (status != 0) {
				perror("pthread_create error");
				exit(status);
			}
		} else {
			int status = pthread_create(&PthreadThreadID, &threadAttribute,
					Thread::startThreadRunnable, (void*) this);
			if (status != 0) {
				perror("pthread_create error");
				exit(status);
			}
		}
	} else {
// set the detachstate attribute to detached
		status = pthread_attr_setdetachstate(&threadAttribute,
				PTHREAD_CREATE_DETACHED);
		if (status != 0) {
			perror("pthread_attr_setdetachstate error");
			exit(status);
		}
		if (runnable.get() == NULL) {
			status = pthread_create(&PthreadThreadID, &threadAttribute,
					Thread::startThread, (void*) this);
			if (status != 0) {
				perror("pthread_create error");
				exit(status);
			}
		} else {
			status = pthread_create(&PthreadThreadID, &threadAttribute,
					Thread::startThreadRunnable, (void*) this);
			if (status != 0) {
				perror("pthread_create error");
				exit(status);
			}
		}
	}
	status = pthread_attr_destroy(&threadAttribute);
	if (status != 0) {
		perror("pthread_attr_destroy error");
		exit(status);
	}
}

void Thread::stop(){
	pthread_exit(NULL);
}
