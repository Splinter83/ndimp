/*
 * Address_Test.cpp
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Address_Test.h"
#include "external_vars.h"


#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

Address_Test::Address_Test() {
	RESTART_LS_WRITE = 0x0001;
}

UINT8 Address_Test::execTest(const BoardInterfaceType& bt, int num_argomenti,
		...) {

	UINT16 CONTROL_BLOCK_POINTER_WRITE = 0x0140;
	UINT16 PROGRAM_POINTER_WRITE = 0x0000;
	RemoteTerminalSide side;

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Address Test***");

	RT_Reg regAddress;
	RT_Reg currentAddres;

	vmeDev->readConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentAddres.raw32);

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;
	side = (RemoteTerminalSide)GlobalData::instance()->GetInterfaceData(bt)->side;
	//Set RT address at 1
	if(side == RT_A){
		regAddress.raw32 = 0; //reset
		regAddress.reg.RTA_A0_W = 0;
		regAddress.reg.RTP_A_W = 1;
	}
	//Test on side B
	else{
		regAddress.raw32 = 0; //reset
		regAddress.reg.RTA_B0_W = 0;
		regAddress.reg.RTP_B_W = 1;
	}

	try {
		UINT8 rt_address = 1;
		//int i = 0;
		for (int i = 0; i < 6; ++i) {
			//Setting RT Address by means VME Adapter
			if(side == RT_A){
				regAddress.raw32 = ((rt_address & 0x3F) << 7); //One-walking on RT-A address, parity included
				regAddress.reg.RTA_A_SEL_W = 1; //Select RTA A
			}
			else{
				regAddress.raw32 = (rt_address & 0x3F); //One-walking on RT-A address, parity included
				regAddress.reg.RTA_B_SEL_W = 1; //Select RTA B
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
			if (rt_add != (rt_address/2)) {
				snprintf(this->strError, MAX_BUF_SIZE,
						"Error during RT Address Test:\n"
						"Unexpected RT address value: the expected value is %d, while read value is %d",
						rt_address/2, rt_add);
				Logger::getLogger()->Log(DEBUG_LEVEL,
						"***Error: ADDRESS TEST: the value expected was %x, the value read is %x***",
						rt_address, rt_add);

				//Reset to previous configuration
				vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentAddres.raw32);
				//Restart
				vmeDev->write(
						GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
						RESTART_LS_WRITE);

				return ERR_RT_ADDR_VAL;
			} else {
				//Parity check. On one walking RT addr is always odd, then odd-parity bit is 0.
				//When 0 then parity has to be 1
				unsigned int parity = (INTERFACE_CONTROL_WORD_READ & RT_ICW_PAR) >> 10;
				if (((parity != 0) && ((rt_add % 2) !=0 )) || // RT != 0
						((parity == 0) && (rt_add == 0))){ // RT = 0
					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during RT Address Test:\n"
							"Parity check error for RT address 0x%01x: the expected value is 0x%01x, while read value is 0x%01x",
							rt_add,(parity+1)%2,parity);
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: ADDRESS TEST: parity check fails***");

					//Reset to previous configuration
					vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentAddres.raw32);
					//Restart
					vmeDev->write(
							GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
							RESTART_LS_WRITE);

					return ERR_RT_ADDR_PARITY;
				}

			}
			rt_address <<= 1;

		}
	} catch (std::string &error) {
		snprintf(this->strError, MAX_BUF_SIZE, "Error during RT Address Test:\n"
				"Unexpected exception: %s", error.c_str());
		return TEST_NOK;
	}

	//Reset to previous configuration
	vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), currentAddres.raw32);
	//Restart
	vmeDev->write(
			GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
			RESTART_LS_WRITE);

	Logger::getLogger()->Log(INFO_LEVEL, "***End Address Test***");

	return TEST_OK;
}

