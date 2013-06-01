/*
 * DiscreteIF.cpp
 *
 *  Created on: 21/nov/2012
 *      Author: galileo
 */

#include "DiscreteIF.h"
#include "GlobalTypes.h"
#include "Logger.h"
#include <stdio.h>
#include "Singleton.h"
#include "ConfigFile.h"


#define SETDISOUT_OFFSET 0x80000
#define DISCRETE_STATUS_OFFSET 0x40000
#define RESETDISOUT_OFFSET 0xC0000

Discrete_IF::Discrete_IF() {
	// TODO Auto-generated constructor stub

}

Discrete_IF::~Discrete_IF() {
	// TODO Auto-generated destructor stub
}

UINT8 Discrete_IF::execTest(const BoardInterfaceType& bt, int num_argomenti , ...){

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Discret I/F Test***");

	UINT32 discrete_io_baseaddress = 0;
	DiscreteReg discrete_reg;
	UINT32 data_read;
	GeneralConfigReg conf_reg;
	UINT32 current_conf;

	discrete_io_baseaddress = GlobalData::instance()->GetInterfaceData(bt)->direct_io;
	vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
	conf_reg.raw32 = current_conf;

	//SETDISOUT activation
	vmeDev->write(discrete_io_baseaddress + SETDISOUT_OFFSET, 1);
	usleep(MSEC_TO_USEC(500));
	//Read DISCRETE STATUS REGISTER
	vmeDev->read(discrete_io_baseaddress + DISCRETE_STATUS_OFFSET, data_read);

	if((data_read & 0x2) != 0){
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: Discrete I/F Test: the expected value after set SETDISOUT to 1 is 0x0001, the read is 0x%01x***",
				discrete_reg.reg.CSMU_WE_TTL);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during Discrete I/F Test:\n"
						"The expected value of DISCRETE STATUS REGISTER after set SETDISOUT to 1 is 0x0000, "
						"while the read value is 0x%04x",data_read);
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
		return ERR_DISCRETE_IF_STATUS_REG_0;
	}

	//Check CSMUWE
	vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal),discrete_reg.raw32);
	if(discrete_reg.reg.CSMU_WE_TTL != 1){
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: Discrete I/F Test: the expected value after set SETDISOUT to 1 is 0x0001, the read is 0x%01x***",
				discrete_reg.reg.CSMU_WE_TTL);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during Discrete I/F Test:\n"
						"The expected value of CSMUWE after set SETDISOUT to 1 is 0x0001, "
						"while the read value is 0x%04x",
						discrete_reg.reg.CSMU_WE_TTL);

		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
		return ERR_DISCRETE_IF_CSMUWE_1;
	}

	vmeDev->write(discrete_io_baseaddress + RESETDISOUT_OFFSET, 1);
	usleep(MSEC_TO_USEC(500));
	//Read DISCRETE STATUS REGISTER
	vmeDev->read(discrete_io_baseaddress + DISCRETE_STATUS_OFFSET, data_read);
	if((data_read & 0x2) != 0x2){
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: Discrete I/F Test: the expected value of RESET_DISOUT after set SETDISOUT to 1 is 0x0001, "
				"while the read value is 0x%01x***",
				data_read);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during Discrete I/F Test:\n"
				"The expected value of DISCRET_STATUS after set SETDISOUT to 1 is 0x0001, "
				"while the read value is 0x%04x",data_read);
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
		return ERR_DISCRETE_IF_RESET_DISOUT_1;
	}

	//Check CSMUWE
	vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal),discrete_reg.raw32);
	if(discrete_reg.reg.CSMU_WE_TTL != 0){
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: Discrete I/F Test: the expected value after set SETDISOUT to 1 is 0x0000, the read is 0x%01x***",
				discrete_reg.reg.CSMU_WE_TTL);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during Discrete I/F Test:\n"
				"The expected value of CSMUWE after set SETDISOUT to 1 is 0x0000, "
				"while the read value is 0x%04x",
				discrete_reg.reg.CSMU_WE_TTL);

		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
		return ERR_DISCRETE_IF_CSMUWE_0;
	}

	// ISNOGO Activation
	conf_reg.reg.SNOGO = 0;
	conf_reg.reg.OVERRIDE = 1;
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),conf_reg.raw32);

	//Reset MCL
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
	usleep(SEC_TO_USEC(2));

	/////////////////////////////////////////////////////////////
	//SETDISOUT activation
	vmeDev->write(discrete_io_baseaddress + SETDISOUT_OFFSET, 1);
	usleep(MSEC_TO_USEC(500));
	//Read DISCRETE STATUS REGISTER
	vmeDev->read(discrete_io_baseaddress + DISCRETE_STATUS_OFFSET, data_read);

	if((data_read & 0x2) != 0x2){
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: Discrete I/F Test: the expected value after set SETDISOUT to 1 is 0x0001, the read is 0x%01x***",
				discrete_reg.reg.CSMU_WE_TTL);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during Discrete I/F Test:\n"
						"The expected value of DISCRETE_STATUS after set SETDISOUT to 1 is 0x0000, "
						"while the read value is 0x%04x",data_read);
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
		usleep(SEC_TO_USEC(2));
		return ERR_DISCRETE_IF_STATUS_REG_0;
	}

	//Check CSMUWE
	vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal),discrete_reg.raw32);
	if(discrete_reg.reg.CSMU_WE_TTL != 0){
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: Discrete I/F Test: the expected value after set SETDISOUT to 1 is 0x0001, the read is 0x%01x***",
				discrete_reg.reg.CSMU_WE_TTL);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during Discrete I/F Test:\n"
				"The expected value of CSMUWE after set SETDISOUT to 1 is 0x0001, "
				"while the read value is 0x%04x",
				discrete_reg.reg.CSMU_WE_TTL);

		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
		usleep(SEC_TO_USEC(2));
		return ERR_DISCRETE_IF_CSMUWE_1;
	}

	//RESETDISOUT activation
	vmeDev->write(discrete_io_baseaddress + RESETDISOUT_OFFSET, 1);
	usleep(MSEC_TO_USEC(500));
	//Read DISCRETE STATUS REGISTER
	vmeDev->read(discrete_io_baseaddress + DISCRETE_STATUS_OFFSET, data_read);

	if((data_read & 0x2) != 0x2){
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: Discrete I/F Test: the expected value after set SETDISOUT to 1 is 0x0001, the read is 0x%01x***",
				discrete_reg.reg.CSMU_WE_TTL);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during Discrete I/F Test:\n"
						"The expected value of DISCRETE_STATUS after set SETDISOUT to 1 is 0x0001, "
						"while the read value is 0x%04x",data_read);
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
		usleep(SEC_TO_USEC(2));
		return ERR_DISCRETE_IF_RESET_DISOUT_0;
	}

	//Check CSMUWE
	vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal),discrete_reg.raw32);
	if(discrete_reg.reg.CSMU_WE_TTL != 0){
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: Discrete I/F Test: the expected value after set SETDISOUT to 1 is 0x0001, the read is 0x%01x***",
				discrete_reg.reg.CSMU_WE_TTL);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during Discrete I/F Test:\n"
						"The expected value of CSMUWE after set SETDISOUT to 1 is 0x0001, "
						"while the read value is 0x%04x",discrete_reg.reg.CSMU_WE_TTL);

		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
		usleep(SEC_TO_USEC(2));
		return ERR_DISCRETE_IF_CSMUWE_1;
	}

	Logger::getLogger()->Log(INFO_LEVEL,
			"***End Discrete I/F Test. Status passed.***");


	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),current_conf);
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
	usleep(SEC_TO_USEC(2));
	return TEST_OK;
}

