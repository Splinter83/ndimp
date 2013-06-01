/*
 * Logger.cpp
 *
 *  Created on: 05/giu/2012
 *      Author: emanuele_galli
 */

/*********************
 * INCLUDES
 *********************/

#include "Logger.h"
#include "ILogger.h"
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/****************
 * LOCAL DEFINES
 ****************/
//#define BUFFER_SIZE 1024

/*********************
 * STATIC ATTRIBUTES
 *********************/
Logger* Logger::myLogger = 0;
ILogger* Logger::_pILogger = 0;
pthread_mutex_t Logger::_mutex= PTHREAD_MUTEX_INITIALIZER;


/**********************
 * METHODS
 **********************/

Logger::Logger() {
	// TODO Auto-generated constructor stub
}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

Logger* Logger::getLogger() {
	//Double check singleton pattern
	if (myLogger == 0) {
		pthread_mutex_lock(&_mutex);
		if (myLogger == 0){
			myLogger = new Logger;
			pthread_mutex_unlock(&_mutex);
			return myLogger;
		}
		else{
			pthread_mutex_unlock(&_mutex);
			return myLogger;
		}
	}
	return myLogger;
}

void Logger::setLogger(ILogger *logger) {
	if (_pILogger != NULL) {
		delete _pILogger;
		_pILogger = 0;
	}
	_pILogger = logger;
}

void Logger::DisableLogLevel(UINT8 level) {
	_pILogger->DisableLogLevel(level);
}

void Logger::EnableLogLevel(UINT8 level) {
	_pILogger->EnableLogLevel(level);
}

bool Logger::IsLevelEnabled(UINT8 level) {
	return _pILogger->IsLevelEnabled(level);
}

void Logger::Log(UINT8 level, const char *logmsg, ...) {

	char buffer[MAX_BUF_SIZE];
	assert(strlen(logmsg) < MAX_BUF_SIZE);

	va_list args;
	va_start (args, logmsg);
	vsprintf (buffer,logmsg, args);
	va_end (args);
	_pILogger->Log(level,buffer);
}

void Logger::ShowLogLevelState() {
	_pILogger->ShowLogLevelState();
}

