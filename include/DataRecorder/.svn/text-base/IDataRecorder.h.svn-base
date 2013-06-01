/*
 * IDataRecorder.h
 *
 *  Created on: 05/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef IDATARECORDER_H_
#define IDATARECORDER_H_

class IRecordable;
class IRecordingDevice;

/*!
 * \interface IDataRecorder
 */
class IDataRecorder {
public:
	IDataRecorder();
	virtual ~IDataRecorder();

	virtual void SetDevice(IRecordingDevice * device) = 0;

	virtual bool Write(IRecordable * recordable) = 0;
};

#endif /* IDATARECORDER_H_ */
