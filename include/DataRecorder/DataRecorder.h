/*
 * DataRecorder.h
 *
 *  Created on: 05/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef DATARECORDER_H_
#define DATARECORDER_H_

#include "IDataRecorder.h"
#include "Thread.h"

#include "Mutex.h"

#include <vector>


class IRecordingDevice;
class IRecordable;
class MutexCondition;

/*!
 * \class DataRecorder
 */
class DataRecorder: public IDataRecorder, public Runnable{
public:
	DataRecorder(IRecordingDevice * device = 0);
	virtual ~DataRecorder();

	void SetDevice(IRecordingDevice * device);

	bool Write(IRecordable * recordable);

	void* run();

private:
	static void* produce(void* arg);
	static void* consume(void*);

	IRecordingDevice* itsIRecordingDevice;

	std::vector<IRecordable*> _queue;

	std::auto_ptr<Thread> _thread;

	MutexCondition  *pCondition;
	Mutex *_pMutex;

	bool _isStopped;


};

#endif /* DATARECORDER_H_ */
