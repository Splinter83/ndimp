/*
 * ILogger.h
 *
 *  Created on: 05/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef ILOGGER_H_
#define ILOGGER_H_

#include "global_definitions.h"
#include "global_types.h"

/*!
 * \enum DataRecLogLevels
 */
enum DataRecLogLevels {
	DEFAULT_LEVEL = 0, //!< DEFAULT_LEVEL
	DEBUG_LEVEL, //!< DEBUG_LEVEL
	WARNING_LEVEL, //!< WARNING_LEVEL
	ERROR_LEVEL, //!< ERROR_LEVEL
	FATAL_LEVEL, //!< FATAL_LEVEL
	INFO_LEVEL, //!< INFO_LEVEL
	TOTAL_LEVEL //!< Cardinality levels
};


/*!
 * \interface ILogger
 */
class ILogger {
public:
	ILogger();
	virtual ~ILogger();

	virtual void DisableLogLevel(UINT8 level) = 0;

	virtual void EnableLogLevel(UINT8 level) = 0;

	virtual bool IsLevelEnabled(UINT8 level) = 0;

	virtual void Log(UINT8 level, const char *logmsg) = 0;

	virtual void ShowLogLevelState() = 0;
};

#endif /* ILOGGER_H_ */
