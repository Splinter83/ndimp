/*
 * LoggerDomain.h
 *
 *  Created on: 05/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef LOGGERDOMAIN_H_
#define LOGGERDOMAIN_H_

class ILogger;
class Logger;

static const int MAX_LEN_LOG_MSG = 256;
static const int MAX_NUM_LOG_LEVEL = 64;
static const int MAX_NUM_MESSAGES = 256;

/*!
 * \enum ePrintDevice
 */
typedef enum {
	unknown = 0, //!< unknown
	onShell = 1, //!< onShell
	onRAM = 2, //!< onRAM
	onFile = 3
//!< onFile
} ePrintDevice;

/*!
 * \struct tLogLevelState
 */
typedef struct {
	int ID;
	bool Enabled;
} tLogLevelState;

static const int TRIALS_NUM = 100;

#endif /* LOGGERDOMAIN_H_ */
