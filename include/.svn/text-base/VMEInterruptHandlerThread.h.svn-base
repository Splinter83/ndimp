/*
 * VMEInterruptHandlerThread.h
 *
 *  Created on: 07/nov/2012
 *      Author: galileo
 */

#ifndef VMEINTERRUPTHANDLERTHREAD_H_
#define VMEINTERRUPTHANDLERTHREAD_H_

#include "BaseRunnableThread.h"
#include "global_types.h"

typedef void (*CallBack)(void*);
typedef INT32 (*WaitFunction)(INT32,UINT32);

class VME_InterruptHandlerThread : public BaseRunnableThread{
public:
	VME_InterruptHandlerThread();
	virtual ~VME_InterruptHandlerThread();
	void setHandler(CallBack callback, void* arg);
	void setWait(WaitFunction wait,INT32 device, UINT32 time = 0);

private:
	void* run();
	CallBack funtionHandler;
	void* _arg;
	WaitFunction waitInterrupt;
	INT32 _device;
	UINT32 _time;
};

inline void VME_InterruptHandlerThread::setHandler(CallBack callback, void* arg){
	funtionHandler = callback;
	_arg = arg;
}

inline void VME_InterruptHandlerThread::setWait(WaitFunction wait, INT32 device, UINT32 time){
	waitInterrupt = wait;
	_device = device;
	_time = time;
}

#endif /* VMEINTERRUPTHANDLERTHREAD_H_ */
