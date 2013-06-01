/*
 * SimpStimpProject: ActiveObject.cpp
 *
 *  Created on: 05/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "ActiveObject.h"
#include "IActiveObjectCommand.h"

#include "MutextCondition.h"
#include "Mutex.h"

#include "Logger.h"

ActiveObject::ActiveObject(const char *name) :
							_Queue(256),
							BaseRunnableThread(name){
	_mutex = new Mutex();
	_mutexCond = new MutexCondition(_mutex);
}

ActiveObject::~ActiveObject() {
	// TODO Auto-generated destructor stub
	delete _mutexCond;
	delete _mutex;
}

void ActiveObject::QueueCommand(IActiveObjectCommand * command){
	_Queue.Push(command);
	//_mutexCond->Signal();
}

void* ActiveObject::run(){
	while(!_isStopped){
		Sleep(1000);
		//_mutexCond->Wait();
		IActiveObjectCommand *command=_Queue.Pop();
		if(command != NULL){
			command->Execute(this);
			command->Destroy();
		}
	}
	return NULL;
}

