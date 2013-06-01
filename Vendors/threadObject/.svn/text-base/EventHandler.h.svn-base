/*
 * EvenetHandler.h
 *
 *  Created on: 19/giu/2012
 *      Author: emanuele_galli
 */

#ifndef EVENETHANDLER_H_
#define EVENETHANDLER_H_

#include "Thread.h"
#include <string.h>

class MutexCondition;

typedef void (*CallBack)(void*);

typedef unsigned short EventId;

#define MAX_NAME_SIZE 32

typedef struct IEvent {
	virtual ~IEvent() {
	}
	;
	virtual void setMessage(const char* msg, unsigned int size) = 0;
	virtual IEvent* clone() = 0;

	EventId Id;
	char Name[MAX_NAME_SIZE];
	char *buffer;

} IEventType;

typedef struct Event: public IEventType {
	Event(const char *eventName_, const EventId & id_) {
		memcpy(Name, eventName_, MAX_NAME_SIZE);
		Id = id_;
	}

	void setMessage(const char* msg, unsigned int size) {
		buffer = new char[size];
		memcpy(buffer, msg, size);
	}

	IEvent* clone() {
		return new Event(this->Name, this->Id);
	}

	~Event() {
		delete[] buffer;
	}
} EventType;

struct EventCompare {
	bool operator()(const EventType& lhs, const EventType& rhs) const {
		return lhs.Id < rhs.Id;
	}
};

class IEventListener {
public:
	virtual void HandleEvent(const IEvent*) = 0;
};

#include <map>
#include <vector>

class EventHandler: public Runnable {

	typedef std::vector<IEventListener*> EventVector;

public:
	void Start();

	static EventHandler* getEventHandler();

	template<typename T>
	void registerEvent(IEventType *event_, IEventListener* listener_) {
		std::map<IEventType*, EventVector*>::iterator it;
		it = _eventMap.find(event_);

		it = _eventMap.begin();

		while (it != _eventMap.end()) {
			if (dynamic_cast<T>(it->first))
				break;
			++it;
		}

		if (it == _eventMap.end()) {
			_eventMap.insert(
					pair<IEventType*, EventVector*>(event_->clone(),
							new std::vector<IEventListener*>(1, listener_)));
		} else {
			it->second->push_back(listener_);
		}
	}

	template<typename T>
	void unregisterEvent(IEventListener *listener_) {
		std::map<IEventType*, EventVector*>::iterator it;
		it = _eventMap.begin();
		while (it != _eventMap.end()) {
			T* event = dynamic_cast<T*>(it->first);
			if (event) {
				_eventMap.erase(it);
			}
			++it;
		}
	}


	void signalEvent(IEventType *event_);

private:
	static EventHandler* _eventHandler;
	EventHandler();
	virtual ~EventHandler();
	void* run();
	static void* setEvent(void* event);
	std::auto_ptr<Thread> _thread;
	bool _isStopped;
	std::map<IEventType*, EventVector*> _eventMap;
	MutexCondition *pCondition;
	static IEventType *_currentEvent;

};

#endif /* EVENETHANDLER_H_ */
