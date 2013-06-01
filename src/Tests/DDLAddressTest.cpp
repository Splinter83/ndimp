/*
 * DDLAddressTest.cpp
 *
 *  Created on: 26/nov/2012
 *      Author: galileo
 */

#include "DDLAddressTest.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#include "Logger.h"
#include "global_types.h"
#include "external_vars.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

DDL_Address_Test::DDL_Address_Test() {
	RESTART_LS_WRITE = 0x0001;
}

DDL_Address_Test::~DDL_Address_Test() {
	// TODO Auto-generated destructor stub
}


UINT8 DDL_Address_Test::execTest(const BoardInterfaceType& bt, int num_argomenti,...){
	UINT16 CONTROL_BLOCK_POINTER_WRITE = 0x0140;
	UINT16 PROGRAM_POINTER_WRITE = 0x0000;
	UINT8 rt_add = 0;
	UINT8 parity = 0;
	UINT32 BASE_ADDRESS;
	RemoteTerminalSide side;
	RT_Reg regAddress;

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	side = (RemoteTerminalSide)GlobalData::instance()->GetInterfaceData(bt)->side;
	//Set RT address at 1
	if(side == RT_A){
		regAddress.raw32 = 0; //reset
		regAddress.reg.RTA_A_SEL_W = 1;
		regAddress.reg.RTP_A_W = 1;
	}
	//Test on side B
	else{
		regAddress.raw32 = 0; //reset
		regAddress.reg.RTA_B_SEL_W = 1;
		regAddress.reg.RTP_B_W = 1;
	}

	vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
	usleep(MSEC_TO_USEC(10));


	//Clear Memory
	for (UINT32 offset = 0;
			offset < GlobalData::instance()->GetInterfaceData(bt)->memory_size;
			offset += 2) {
		vmeDev->write(BASE_ADDRESS + offset, 0x0);
	}

	vmeDev->write(BASE_ADDRESS + CB_POINTER_OFFSET, CONTROL_BLOCK_POINTER_WRITE);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_OFFSET, PROGRAM_POINTER_WRITE);


	//Restart
	vmeDev->write(
			GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
			RESTART_LS_WRITE);

	usleep(MSEC_TO_USEC(5));

	vmeDev->read(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 +
			LS_RT_INTERFACE_CONTROL_WORD_OFFSET,
			INTERFACE_CONTROL_WORD_READ);

	rt_add = INTERFACE_CONTROL_WORD_READ & RT_ICW_TA;
	rt_add >>= 11;

	if(rt_add != 0){
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during EDDL RT Address Test:\n"
				"Unexpected RT address value: the expected value is 0, while read value is %d",
				rt_add);
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: EDDL RT ADDRESS TEST: the value expected was 0, the value read is %x***",
				rt_add);
		//Reset to previous configuration
		vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), 0);
		//Restart
		vmeDev->write(
				GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
				RESTART_LS_WRITE);
		return TEST_NOK;
	}

	parity = (INTERFACE_CONTROL_WORD_READ & RT_ICW_PAR) >> 10;

	if(parity == 0){
		snprintf(this->strError, MAX_BUF_SIZE,
					"Error during EDDL RT Address Test:\n"
					"Unexpected parity RT address value: the expected value is 1, while read value is %d",
					rt_add);
		Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: EDDL RT ADDRESS parity TEST: the value expected was 1, the value read is %x***",
					rt_add);
		//Reset to previous configuration
		vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), 0);
		//Restart
		vmeDev->write(
				GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
				RESTART_LS_WRITE);
		return TEST_NOK;
	}

	return TEST_OK;
}
