/*
 * global_definitions.h
 *
 *  Created on: 06/giu/2012
 *  Author: Emanuele Galli
 *
  *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef GLOBAL_DEFINITIONS_H_
#define GLOBAL_DEFINITIONS_H_

/******************
 * DEFINES
 ******************/

#define MAX_BUF_SIZE 1024

#ifndef NULL
	#define NULL 0
#endif


static const char* const LOG_LEVEL_STRING[] = {"DEFAULT",
											   "DEBUG",
											   "WARNING",
											   "ERROR",
											   "FATAL",
											   "INFO"}; ///Log level string

#define DEBUG  //commentare per la versione finale

//#define VME_PRESENT //if VME board is present

//#define VME_RESET_SW_ADDRESS 		0x20000018 ///SW reset
//#define VME_CONF_BASE_ADDRESS       0x20000000 /// Base address
#define VME_DISCRETE_OUT_REG 		0x44 ///Dicrete Out Not Critical
//#define VME_HANDOVER_RESET          0x3C /// Handover reset
//#define VME_INTERRUPT_RESET 	    0x08 ///Interrupt Reset
//#define VME_GENERAL_CONF_ADDRESS 	0x14 ///Configuration registry address
//#define VME_DISCRETE_IO_ADDRESS 	0x18 /// Discrete I/O registry address (STIMP)
#define VME_1553_ADDRESS 			0x1C /// 1553 registry address (SIMP)
//#define VME_HANDOVER_REG 			0x20 /// Handover registry address
//#define VME_SGA_ADDRESS 			0x24 ///Sga registry address
//#define VME_REMOTE_TERM_ADDRESS 	0x28 /// Remote terminal registry address
//#define VME_FOFE_ADDRESS 	        0x2C /// Control FOFE address
#define VME_RESET_SW_REG            0x30 /// Force VME reset adapter
//#define VME_MCL_REG					0x38 /// Force Board Reset
#define VME_ACTDEM_REG              0x40 /// ACT DEM Register
//#define VME_INTERRUPT_REG			0x34 /// Interrupt registry

//#define MAX_NAME_SIZE 255

//#define HEADER_DELIMETER 0xFFFF

#define USEC_TO_NSEC(x) (x*1000)
#define MSEC_TO_USEC(x) (x*1000)
#define SEC_TO_MSEC(x) (x*1000)
#define SEC_TO_USEC(x) (MSEC_TO_USEC(x*1000))


#define XSD_PATH_NAME "./XSD/"


#endif /* GLOBAL_DEFINITIONS_H_ */
