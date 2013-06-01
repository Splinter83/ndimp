/*
 * Thread.h
 *
 *  Created on: 06/giu/2012
 *      Author: emanuele_galli
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <memory>
#include <pthread.h>

class Runnable {
public:
	virtual void* run() = 0;
	virtual ~Runnable() = 0;
	void Sleep(unsigned int usleep);
};


using namespace std;

class Thread {
public:
	Thread(auto_ptr<Runnable> runnable_, bool isDetached = false);
	Thread(bool isDetached = false);
	virtual ~Thread();
	void start();
	void* join();
	void stop();
private:
	pthread_t PthreadThreadID; // thread ID
	bool detached; // true if thread created in detached state; false otherwise
	pthread_attr_t threadAttribute;
	auto_ptr<Runnable> runnable;
	Thread(const Thread&);
	const Thread& operator=(const Thread&);
	void setCompleted();
	void* result; // stores return value of run()
	virtual void* run() {
		return 0;
	}
	static void* startThreadRunnable(void* pVoid);
	static void* startThread(void* pVoid);
	void PrintError(char* msg, int status, char* fileName, int lineNumber);
};

#endif /* THREAD_H_ */
