/*
 * Parity_Test.cpp
 *
 *  Created on: 08/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Parity_Test.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

Parity_Test::Parity_Test() {
	CONTROL_BLOCK_POINTER_WRITE = 0x00A8;
	PROGRAM_POINTER_WRITE = 0x0000;
	RESTART_LS_WRITE = 0x0001;
}

UINT8 Parity_Test::execTest(const BoardInterfaceType& bt, int num_argomenti,
		...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Parity Test***");
	RemoteTerminalSide side;

	RT_Reg regAddress;
	UINT32 currentConfiguration; //Save current remote terminal configuration. It will be set again at the end of test

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Parity Test step 1***");

	vmeDev->readConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentConfiguration);

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	side = (RemoteTerminalSide)GlobalData::instance()->GetInterfaceData(bt)->side;
	//Parity error simulation
	// Test on Side A
	if(side == RT_A){
		regAddress.raw32 = 0; //reset
		regAddress.reg.RTA_A0_W = 0;
		regAddress.reg.RTP_A_W = 0;
		regAddress.reg.RTA_A_SEL_W = 1;
	}
	//Test on side B
	else{
		regAddress.raw32 = 0; //reset
		regAddress.reg.RTA_B0_W = 0;
		regAddress.reg.RTP_B_W = 0;
		regAddress.reg.RTA_B_SEL_W = 1;
	}

	vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
	usleep(MSEC_TO_USEC(5));
	//Clear memory
	for (UINT32 offset = 0;
			offset < GlobalData::instance()->GetInterfaceData(bt)->memory_size;
			offset += 2) {
		vmeDev->write(BASE_ADDRESS + offset, 0x0);
	}
	vmeDev->write(BASE_ADDRESS + CB_POINTER_OFFSET,
			CONTROL_BLOCK_POINTER_WRITE);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_OFFSET, PROGRAM_POINTER_WRITE);
	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
			RESTART_LS_WRITE);

	usleep(MSEC_TO_USEC(5));

	vmeDev->read(
			BASE_ADDRESS
					+ CONTROL_BLOCK_POINTER_WRITE
							* 2+ INTERFACE_STATUS_WORD_OFFSET,
			INTERFACE_STATUS_WORD_READ);
	if (INTERFACE_STATUS_WORD_READ != 0x0008) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: INTERFACE STATUS WORD: the value expected was 0008, the value read is %x***",
				INTERFACE_STATUS_WORD_READ);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during RT Parity Address Test (odd-parity error enabled):\n"
						"The expected value for the Interface Status Word Value is 0x0008, while the read value is 0x%04x",
				INTERFACE_STATUS_WORD_READ);

		//Reset to previous configuration
		vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentConfiguration);
		//Restart
		vmeDev->write(
				GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
				RESTART_LS_WRITE);

		return ERR_PAR_STATUS_WORD_PARITY_ERROR;
	}
	vmeDev->read(
			BASE_ADDRESS
					+ CONTROL_BLOCK_POINTER_WRITE
							* 2+ LS_RT_ERROR_BITE_WORD_OFFSET,
			LS_RT_ERROR_BITE_WORD_READ);
	if (LS_RT_ERROR_BITE_WORD_READ != 0x0004) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: LS RT ERROR BITE WORD: the value expected was 0004, the value read is %x***",
				LS_RT_ERROR_BITE_WORD_READ);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during RT Parity Address Test (odd-parity error enabled):\n"
						"The expected value for the Error/BITE Word Value is 0x0004, while the read value is 0x%04x",
				ERR_PAR_BITE_WORD_PARITY_ERROR);

		//Reset to previous configuration
		vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentConfiguration);
		usleep(MSEC_TO_USEC(10));
		//Restart
		vmeDev->write(
				GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
				RESTART_LS_WRITE);

		return ERR_PAR_BITE_WORD_PARITY_ERROR;
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Parity Test step 2***");
	//Remove error simulation
	// Test on Side A
	if(side == RT_A){
		regAddress.raw32 = 0; //reset
		regAddress.reg.RTA_A0_W = 0;
		regAddress.reg.RTP_A_W = 1;
		regAddress.reg.RTA_A_SEL_W = 1;
	}
	//Test on side B
	else{
		regAddress.raw32 = 0; //reset
		regAddress.reg.RTA_B0_W = 0;
		regAddress.reg.RTP_B_W = 1;
		regAddress.reg.RTA_B_SEL_W = 1;
	}
	vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);

	//Clear memory
	for (UINT32 k = 0;
			k < GlobalData::instance()->GetInterfaceData(bt)->memory_size; k +=
					2) {
		vmeDev->write(BASE_ADDRESS + k, 0x0);
	}
	vmeDev->write(BASE_ADDRESS + CB_POINTER_OFFSET,
			CONTROL_BLOCK_POINTER_WRITE);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_OFFSET, PROGRAM_POINTER_WRITE);
	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
			RESTART_LS_WRITE);

	usleep(MSEC_TO_USEC(2));

	vmeDev->read(
			BASE_ADDRESS
					+ +CONTROL_BLOCK_POINTER_WRITE
							* 2+ INTERFACE_STATUS_WORD_OFFSET,
			INTERFACE_STATUS_WORD_READ);
	if (INTERFACE_STATUS_WORD_READ != 0x0000) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: INTERFACE STATUS WORD: the value expected was 0020, the value read is %x***",
				INTERFACE_STATUS_WORD_READ);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during RT Parity Address Test (odd-parity error disabled):\n"
						"The expected value for the Interface Status Word Value is 0x0020, while the read value is 0x%04x",
				INTERFACE_STATUS_WORD_READ);

		//Reset to previous configuration
		vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentConfiguration);
		usleep(MSEC_TO_USEC(10));
		//Restart
		vmeDev->write(
				GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
				RESTART_LS_WRITE);

		return ERR_PAR_STATUS_WORD;
	}
	vmeDev->read(
			BASE_ADDRESS
					+ CONTROL_BLOCK_POINTER_WRITE
							* 2+ LS_RT_ERROR_BITE_WORD_OFFSET,
			LS_RT_ERROR_BITE_WORD_READ);
	if (LS_RT_ERROR_BITE_WORD_READ != 0x0000) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: LS RT ERROR BITE WORD: the value expected was 0000, the value read is %x***",
				LS_RT_ERROR_BITE_WORD_READ);
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during RT Parity Address Test (odd-parity error disabled):\n"
						"The expected value for the Error/BITE Word Value is 0x0000, while the read value is 0x%04x",
				ERR_PAR_BITE_WORD_PARITY_ERROR);

		//Reset to previous configuration
		vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentConfiguration);
		usleep(MSEC_TO_USEC(10));
		//Restart
		vmeDev->write(
				GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
				RESTART_LS_WRITE);

		return ERR_PAR_BITE_WORD;
	}


	//Reset to previous configuration
	vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentConfiguration);
	usleep(MSEC_TO_USEC(10));
	//Restart
	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
			RESTART_LS_WRITE);

	Logger::getLogger()->Log(INFO_LEVEL, "***End Parity Test***");

	return TEST_OK;
}

