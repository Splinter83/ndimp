/*
 * FilestreamDevice.cpp
 *
 *  Created on: 07/giu/2012
 *      Author: emanuele_galli
 */

#include "FilestreamDevice.h"

#include <time.h>
#include <string.h>
#include "global_definitions.h"
#include "global_types.h"

#include <iostream>

FilestreamDevice::FilestreamDevice(const char *filename) : _file(NULL) {
	UINT32 size = 0;
	if (filename != NULL) {
		if ((size = strlen(filename)) > 0) {
			_pfilename = new char[strlen(filename)];
			memcpy(_pfilename,filename,size);
			return;
		}
	}

	struct tm * timeinfo;
	time_t rawtime;
	char time_buffer[30] = {0};
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(time_buffer, 30, "%Y%m%d_%H%M%S ", timeinfo);

	size = strlen(time_buffer) + sizeof("LOG_") + 1;
	_pfilename = new char[size];
	memset(_pfilename,0,size);
	sprintf(_pfilename,"LOG_%s.txt",time_buffer);
}

FilestreamDevice::~FilestreamDevice() {
	delete []_pfilename;
	Close();
}

void FilestreamDevice::Close() {
	if(_file != NULL)
		fclose(_file);
}

bool FilestreamDevice::Open() {
	if(_file != NULL)
		return true;
	if((_file = fopen(_pfilename,"w")) == NULL)
		return false;
	return true;
}

int FilestreamDevice::Write(const char* buffer, int size) {
#ifdef WIN32
    char *locBuffer = new char[size+1];
#else
	char locBuffer [size+1];
#endif
	std::cout << buffer << std::endl;
	memset(locBuffer,0,size+1);
	memcpy(locBuffer, buffer, size);
	std::cout << locBuffer << std::endl;
	// termina stringa
	size = fprintf(_file,"%s\n",locBuffer);
	fflush(_file);
    // come feedback restituisce la dimensione dell'ultimo messaggio ricevuto
#ifdef WIN32
	delete []locBuffer;
#endif
    return(size);
}
