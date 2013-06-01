/*
 * SimpStimpProject: OOQueue.h
 *
 *  Created on: 05/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef OOQUEUE_H_
#define OOQUEUE_H_

#include <queue>

template <class T>
class OOQueue {
public:
	OOQueue(int max_msgs) : _Maxmsgs(max_msgs){

	}

	virtual ~OOQueue(){
		while(_Queue.size() > 0)
			_Queue.pop();
	}

	T Front(){
		if(_Queue.size() == 0)
			return 0;
		T frontElement = _Queue.front();
		return frontElement;
	}

	T Pop(){
		if(_Queue.size() == 0)
			return 0;
		T frontElement = _Queue.front();
		_Queue.pop();
		return frontElement;
	}

	bool Push(T element){
		if((int)_Queue.size() > _Maxmsgs)
			return false;
		_Queue.push(element);
		return true;
	}

private:
	std::queue<T> _Queue;
	int _Maxmsgs;
};

#endif /* OOQUEUE_H_ */
