/*
 * EvenetHandler.cpp
 *
 *  Created on: 19/giu/2012
 *      Author: emanuele_galli
 */

#include "EventHandler.h"
#include "MutextCondition.h"

#include "Mutex.h"
#include <stdio.h>

EventHandler* EventHandler::_eventHandler = NULL;
IEventType* EventHandler::_currentEvent = NULL;


EventHandler::EventHandler() : _thread(
		new Thread(auto_ptr<Runnable>(this))){
	_isStopped = true;
	pCondition = new MutexCondition(new Mutex);
}

EventHandler::~EventHandler() {
	delete _eventHandler;
}


void EventHandler::Start(){
	_isStopped = false;
	_thread->start();
}

EventHandler* EventHandler::getEventHandler(){
	Mutex mutex;
	if(_eventHandler == NULL){
		mutex.Lock();
		if(_eventHandler == NULL){
			_eventHandler = new EventHandler;
		}
		mutex.Unlock();
	}
	return _eventHandler;
}

void* EventHandler::run(){
	while(!_isStopped){
		pCondition->Wait();
		std::map<IEventType*, EventVector*>::iterator it;
		it = _eventMap.begin();
		if(it != _eventMap.end()){
			for (unsigned int i = 0; i < it->second->size();++i){
				it->second->at(i)->HandleEvent(EventHandler::_currentEvent);
			}
			++it;
		}
		else{
			char buffErr[20];
			sprintf(buffErr,"Unknown Event (%d) %s", _currentEvent->Id, _currentEvent->Name);
			perror(buffErr);
		}
	}
	return 0;
}

void* EventHandler::setEvent(void* event){
	EventHandler::_currentEvent = (static_cast<IEventType*>(event));
	return 0;
}


void EventHandler::signalEvent(IEventType *eventName){
	pCondition->Signal(&(EventHandler::setEvent),(void*)eventName);
}



