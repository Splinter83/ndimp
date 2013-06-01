/*
 * LoggerBase.h
 *
 *  Created on: 05/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef LOGGERBASE_H_
#define LOGGERBASE_H_

#include "ILogger.h"

#include "LoggerDomain.h"

class LoggerBase: public ILogger {
public:
	LoggerBase();
	virtual ~LoggerBase();

	virtual void DisableLogLevel(UINT8 level);

	virtual void EnableLogLevel(UINT8 level);

	virtual bool IsLevelEnabled(UINT8 level);

	virtual void ShowLogLevelState();

private:
	void ResetLogLevelState();

	tLogLevelState logLevelStateVector[MAX_NUM_LOG_LEVEL];
};

#endif /* LOGGERBASE_H_ */
