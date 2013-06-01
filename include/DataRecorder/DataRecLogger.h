/*
 * DataRecLogger.h
 *
 *  Created on: 05/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef DATARECLOGGER_H_
#define DATARECLOGGER_H_

class ILogger;

#include "LoggerBase.h"

#include "DataRecorder.h"

/*!
 * \class DataRecLogger
 * \brief Logs data into data recorder
 */
class DataRecLogger: public LoggerBase {
public:
	/*!
	 * Constructor
	 * @param dataRec Pointer to data recorder interface
	 */
	DataRecLogger(DataRecorder *dataRec); ///< Constructor
	virtual ~DataRecLogger(); ///< Destructor

	/*!
	 *
	 * @param level
	 * @param logmsg
	 */
	void Log(UINT8 level, const char * logmsg);

private:
	DataRecorder *_pDataRecorder; ///< Pointer to IDataRecorder
};

#endif /* DATARECLOGGER_H_ */
