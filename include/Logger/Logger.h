/*
 * Logger.h
 *
 *  Created on: 05/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <pthread.h>
#include <time.h>
#include "global_definitions.h"

#include "ILogger.h"

/**
 * @class Logger
 * Singleton for logging
 */
class Logger {
public:
	static Logger* getLogger();

	void setLogger(ILogger *logger);

	virtual ~Logger();

	void DisableLogLevel(UINT8 level);

	void EnableLogLevel(UINT8 level);

	bool IsLevelEnabled(UINT8 level);

	void Log(UINT8 level, const char *logmsg, ...);

	void ShowLogLevelState();

	/**TODO
	 * Add multiple devices
	 * void addLogger(ILogger *new_logger){logger_list.push_back(new_logger;}
	 * int removeDevice(ILogger *logger){for(UINT32 i=0; i < logger_list.size();++i)
	 * 	                                 if(logger_list[i] == logger){
	 * 	                                 	logger_list.remove(i);
	 * 	                                 	break;
	 * 	                                 }
	 * 	                                 };
	 *
	 * std::vector<ILogger*> logger_list;
	 */

private:
	Logger(void);
	static Logger *myLogger;
	static ILogger *_pILogger;

	static pthread_mutex_t _mutex;
};

#endif /* LOGGER_H_ */
