/*
 * SimpStimpProject: TsapMessage.h
 *
 *  Created on: 08/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef TSAPMESSAGE_H_
#define TSAPMESSAGE_H_

#include "global_types.h"

struct LogMsg{
	//static const int MAX_MSG_SIZE = 1024;
	LogMsg(const char* msg, const UINT32 &size){
		_size = size;
		_buffer = new char[size];
		memset(_buffer,0,size);
		memcpy(_buffer,msg,size);
	}

	~LogMsg(){
		delete []_buffer;
	}

	char *_buffer;
	int _size;
};

/*struct DiscreteMsg{
	DiscreteMsg(const std::vector<DiscreteField> vect){
		_discreteVect = vect;
	}
	std::vector<DiscreteField> _discreteVect;
};*/

struct DiscreteMsg{
	//static const int MAX_MSG_SIZE = 1024;
	DiscreteMsg(const char* msg, const UINT32 &size){
		_size = size;
		_buffer = new char[size];
		memset(_buffer,0,size);
		memcpy(_buffer,msg,size);
	}

	~DiscreteMsg(){
		delete []_buffer;
	}

	char *_buffer;
	int _size;
};


#endif /* TSAPMESSAGE_H_ */
