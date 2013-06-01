/*
 * VMEInterruptHandlerThread.cpp
 *
 *  Created on: 07/nov/2012
 *      Author: galileo
 */

#include "VMEInterruptHandlerThread.h"

VME_InterruptHandlerThread::VME_InterruptHandlerThread() : BaseRunnableThread("VME_InterruptHandler") {
	// TODO Auto-generated constructor stub

}

VME_InterruptHandlerThread::~VME_InterruptHandlerThread() {
	// TODO Auto-generated destructor stub
}

void* VME_InterruptHandlerThread::run(){
	_isStopped = false;
	while(!_isStopped){
		waitInterrupt(_device,_time);
		funtionHandler(_arg);
	}
}

