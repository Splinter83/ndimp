/*
 * IRecordingDevice.h
 *
 *  Created on: 06/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef IRECORDINGDEVICE_H_
#define IRECORDINGDEVICE_H_

/*!
 * \interface IRecordingDevice
 */
class IRecordingDevice {
public:
	IRecordingDevice();
	virtual ~IRecordingDevice();

	virtual void Close() = 0;
	virtual bool Open() = 0;
	virtual int Write(const char* buffer, int size) = 0;
};

#endif /* IRECORDINGDEVICE_H_ */
