/*
 * SimpStimpProject: ActiveObject.h
 *
 *  Created on: 05/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef ACTIVEOBJECT_H_
#define ACTIVEOBJECT_H_

#include "ActivationQueue.h"
#include "BaseRunnableThread.h"

class MutexCondition;
class Mutex;

class IActiveObjectCommand;

class ActiveObject : public BaseRunnableThread{
public:
	ActiveObject(const char *name);
	virtual ~ActiveObject();

	void QueueCommand(IActiveObjectCommand * command);

protected:
	void* run();

private:
	 ActivationQueue _Queue;
	 MutexCondition *_mutexCond;
	 Mutex *_mutex;
};

#endif /* ACTIVEOBJECT_H_ */
