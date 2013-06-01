/*
 * SimpStimpProject: BaseRunnableThread.h
 *
 *  Created on: 03/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef BASERUNNABLETHREAD_H_
#define BASERUNNABLETHREAD_H_

#include "Thread.h"

class BaseRunnableThread : public Runnable{
public:
	BaseRunnableThread();
	BaseRunnableThread(const char* name);
	virtual ~BaseRunnableThread();

	virtual void Start();
	virtual void Stop();

	bool GetStatus() const;
	char *GetName() const;

protected:
	virtual void* run();

protected:
	bool _isStopped;
	char *_name;
	std::auto_ptr<Thread> _thread;
};

inline bool BaseRunnableThread::GetStatus() const{
	return _isStopped;
}

inline char *BaseRunnableThread::GetName() const{
	return _name;
}

#endif /* BASERUNNABLETHREAD_H_ */
