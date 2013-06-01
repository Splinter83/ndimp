/*
 * Discrete_Output.cpp
 *
 *  Created on: 29/11/2012
 *      Author: savino
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Discrete_Output.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

Discrete_Output::Discrete_Output() {

}

UINT8 Discrete_Output::execTest(const BoardInterfaceType& bt, int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Test Discrete Output***");

	va_list argP;
	va_start(argP, num_argomenti);
	int critical = va_arg(argP, int);
	va_end(argP);

	UINT32 DIRECT_IO  = GlobalData::instance()->GetInterfaceData(bt)->direct_io;
	UINT32 WR_REG = 0x0;

	DiscreteReg discreteReg;
	discreteReg.raw32 = 0x0;
	UINT32 data_read, offset;

	if (critical) {


		WR_REG = DIRECT_IO + 0x100000;
		vmeDev->write(WR_REG, 0xF);

		//Enable ISNOGO
		WR_REG = DIRECT_IO + 0x18000E;
		vmeDev->write(WR_REG, 0x0);


		usleep(100);

		vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal), discreteReg.raw32);

		offset = 0xC;
		for(int i=0; i < 4; i++)
		{
			//DO_(1...4)
			if(  ((discreteReg.raw32 >> offset) & 0x01) != 1)
			{
				printError(1, discreteReg.raw32 );
				return ERR_DISCR_OUT_ONE_WALK_CRITICAL;
			}

			offset++;
		}

		//Disable ISNOGO
		WR_REG = DIRECT_IO + 0x18000C;
		vmeDev->write(WR_REG, 0x1);

		//TriState????????

	} else {

		GeneralConfigReg conf_reg;
		UINT32 current_conf;

		vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal), current_conf);
		conf_reg.raw32 = current_conf;

		// ISNOGO De-Activation
		conf_reg.reg.SNOGO = 1;
		conf_reg.reg.OVERRIDE = 1;
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),conf_reg.raw32);

		WR_REG = DIRECT_IO + 0x280000;

		offset = 0x01;
		UINT32 check = 0x11;
		for(int i = 0; i < 8; i++)
		{
			vmeDev->write(WR_REG, offset);

			usleep( MSEC_TO_USEC(100) );

			vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal), discreteReg.raw32);

			//Read_back
			vmeDev->read(DIRECT_IO + 0x280002, data_read );

			UINT32 data = data_read & check;

			if( data != check )
			{
				if((data & 0x0F0F) != (check & 0x0F0F)){
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: Bit Discrete Output Test: the value expected in the uno walking was %x, the value read is %x***",
							(check & 0xF0F0), (data & 0xF0F0));

					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during Discrete Output Test (BIT EO[5-12]):\n"
							"Expected value during one-walking test at vme-address 0x%04x"
							"is 0x%04x, while read value is 0x%04x.",
							Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal), (check & 0x0F0F), (data & 0x0F0F));
					return ERR_DISCR_OUT_ONE_WALK_NOT_CRITICAL_AFTER;
				}
				else if ((data & 0xF0F0) != (check & 0xF0F0)){
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: Bit Discrete Output Test: the value expected in the uno walking was %x, the value read is %x***",
							(check & 0xF0F0), (data & 0xF0F0));

					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during Discrete Output Test (BIT IO[5-12]):\n"
							"Expected value during one-walking test at vme-address 0x%04x"
							"is 0x%04x, while read value is 0x%04x.",
							Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal), (check & 0xF0F0), (data & 0xF0F0));
					return ERR_DISCR_OUT_ONE_WALK_NOT_CRITICAL_BEFORE;
				}
			}

			if(i == 3){
				offset <<= 5;
				check <<=5;
			}
			else{
				offset <<=1;
				check <<=1;
			}

		}

		//vmeDev->writeConf(VME_DISCRETE_OUT_REG, 0xF0F0);
		usleep(SEC_TO_MSEC(1));
	}


	vmeDev->write(0x28E80000, 0x3030);

	Logger::getLogger()->Log(INFO_LEVEL, "***End Test Discrete Output***");
	return TEST_OK;
}



void Discrete_Output::printError(UINT32 expected, UINT32 read)
{
	Logger::getLogger()->Log(DEBUG_LEVEL,
			"***Error: Bit Discrete Input Test: the value expected in the uno walking was %x, the value read is %x***",
			expected,read );

	snprintf(this->strError, MAX_BUF_SIZE,
			"Error during Discrete Input Test:\n"
			"Expected value during one-walking test at vme-address 0x%04x"
			"is 0x%04x, while read value is 0x%04x.",
			Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal), expected,read);
}
