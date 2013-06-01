/*
 * FilestreamDevice.h
 *
 *  Created on: 07/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef FILESTREAMDEVICE_H_
#define FILESTREAMDEVICE_H_

#include <stdio.h>
#include "IRecordingDevice.h"

/*!
 * \class FilestreamDevice
 */
class FilestreamDevice : public IRecordingDevice{
public:
	/*!
	 * File name. If it is not set, default file name is used. Default value is Log_yearmonthday_hhmmss.log
	 * @param filename
	 * @param size
	 */
	FilestreamDevice(const char *filename = NULL);
	virtual ~FilestreamDevice();

	/*!
	 * Closes log file
	 */
	void Close();

	/*!
	 * Open log file
	 */
	bool Open();

	/*!
	 * Writes log data on file
	 * @param buffer
	 * @param size
	 * @return Number of bytes written
	 */
	int Write(const char* buffer, int size);

private:

	char* _pfilename;
	FILE *_file;

};

#endif /* FILESTREAMDEVICE_H_ */
