/*
 * SimpStimpProject: BaseRunnableThread.cpp
 *
 *  Created on: 03/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "BaseRunnableThread.h"
#include <iostream>
#include <string.h>

BaseRunnableThread::BaseRunnableThread() :
                    _thread(new Thread(std::auto_ptr<Runnable>(this))) {
	_name = new char [strlen("BaseRunnableThread")];
	strcpy(_name,"BaseRunnableThread");
	_isStopped = true;
}

BaseRunnableThread::BaseRunnableThread(const char* name) :
					_thread(new Thread(std::auto_ptr<Runnable>(this))){
	_name = new char [strlen(name)];
	strcpy(_name,name);
	std::cout << "Thread" <<_name<<" Started!"<<std::endl;
	_isStopped = true;
}


BaseRunnableThread::~BaseRunnableThread() {
	this->Stop();
	delete [] _name;
}

void BaseRunnableThread::Start() {
	this->_isStopped = false;
	this->_thread->start();
}

void BaseRunnableThread::Stop() {
	this->_isStopped = true;
	std::cout << "Thread" <<_name<<" Stopped!"<<std::endl;
	//this->_thread->stop();
}

void* BaseRunnableThread::run(){
	while(!_isStopped)
		Sleep(1000);

	return NULL;
}
