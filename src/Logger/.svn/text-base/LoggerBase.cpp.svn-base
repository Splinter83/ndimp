/*
 * LoggerBase.cpp
 *
 *  Created on: 05/giu/2012
 *      Author: emanuele_galli
 */

#include "LoggerBase.h"

#include <stdio.h>
#include <string.h>

LoggerBase::LoggerBase() {
	ResetLogLevelState();
}

LoggerBase::~LoggerBase() {
	// TODO Auto-generated destructor stub
}

void LoggerBase::DisableLogLevel(UINT8 level) {
	//#[ operation DisableLogLevel(int)
	logLevelStateVector[level].ID = 0;
	logLevelStateVector[level].Enabled = false;
	//#]
}

void LoggerBase::EnableLogLevel(UINT8 level) {
	//#[ operation EnableLogLevel(int)
	logLevelStateVector[level].ID = level;
	logLevelStateVector[level].Enabled = true;

	//#]
}

bool LoggerBase::IsLevelEnabled(UINT8 level) {
	//#[ operation IsLevelEnabled(int)
	return (logLevelStateVector[level].Enabled);
	//#]
}

void LoggerBase::ShowLogLevelState() {
	//#[ operation ShowlogLevelState()
	for (int iter = 0; iter < MAX_NUM_LOG_LEVEL; iter++)
		printf("logLevelStateVector[%d] - ID %d - En %d\n", iter,
				logLevelStateVector[iter].ID,
				logLevelStateVector[iter].Enabled);
	//#]
}

void LoggerBase::ResetLogLevelState() {
	//#[ operation ResetlogLevelState()
	memset(&logLevelStateVector[0], 0x00,
			sizeof(tLogLevelState) * MAX_NUM_LOG_LEVEL);
	//#]
}
