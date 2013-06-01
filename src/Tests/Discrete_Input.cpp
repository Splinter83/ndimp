/*
 * Discrete_Input.cpp
 *
 *  Created on: 27/11/12
 *      Author: savino
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#include "Discrete_Input.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

Discrete_Input::Discrete_Input() {

}

UINT8 Discrete_Input::execTest(const BoardInterfaceType& i,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Test Discrete Input***");

	va_list argP;
	va_start(argP, num_argomenti);
	int critical = va_arg(argP, int);
	va_end(argP);

	UINT32        data_read, data_read_opt;
	DiscreteReg   discreteReg;
	Interrupt_Reg interruptReg;

	interruptReg.raw32 = 0xFFFFFFFF;

	if( critical )
	{
		discreteReg.raw32 = 0x1;

		for(int i = 0; i < 4; i++)
		{

			vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal), discreteReg.raw32);

			usleep( MSEC_TO_USEC(100) );

			vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_INTERRUPT_REG", hexadecimal), data_read);

			Logger::getLogger()->Log(DEBUG_LEVEL,
										"data_read=%x interruptReg.raw32=%x i=%d",
										data_read, interruptReg.raw32, i );
			usleep( MSEC_TO_USEC(100) );

			switch(i)
			{
				case 0:

					if( interruptReg.reg.DI1_INT != ( (data_read >> 12) & 0x01) )
					{
						printError( interruptReg.reg.DI1_INT, data_read );
						return ERR_DISCR_ONE_WALK_CRITICAL_DI1_INT;
					}
					break;
				case 1:
					if( interruptReg.reg.DI2_INT != ( ( data_read >> 4 )& 0x01) )
					{
						printError( interruptReg.reg.DI2_INT, data_read );
						return ERR_DISCR_ONE_WALK_CRITICAL_DI2_INT;
					}
					break;
				case 2:
					if( interruptReg.reg.DI3_INT != (( data_read >> 11 ) & 0x01) )
					{
						printError( interruptReg.reg.DI3_INT, data_read );
						return ERR_DISCR_ONE_WALK_CRITICAL_DI3_INT;

					}
					break;
				case 3:
					if( interruptReg.reg.DI4_INT != (( data_read >> 3) & 0x01) )
					{
						printError( interruptReg.reg.DI4_INT, data_read );
						return ERR_DISCR_ONE_WALK_CRITICAL_DI4_INT;
					}
					break;
			}

			discreteReg.raw32 <<=1;
			data_read = 0;
		}

	}
	else
	{
		discreteReg.raw32 = 0x10;

		UINT32 NOT_CRITICAL_REG = 0x28E80000;

		vmeDev->write(NOT_CRITICAL_REG, 0x3030);

		vmeDev->write(0x28CC0000, 0x1);

		for(int i = 0; i < 8; i++)
		{
			vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal), discreteReg.raw32);

			usleep( MSEC_TO_USEC(100) );

			vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_INTERRUPT_REG", hexadecimal), data_read);

			vmeDev->read(NOT_CRITICAL_REG , data_read_opt);


			Logger::getLogger()->Log(DEBUG_LEVEL,
										"data_read=%x interruptReg.raw32=%x i=%d",
										data_read, interruptReg.raw32, i );


			usleep( MSEC_TO_USEC(100) );

			switch(i)
			{
				case 0:
					if( (data_read_opt & 0x1) != 1)
					{
						printError( 1, data_read_opt );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI5_INT;
					}

					if( interruptReg.reg.DI5_INT != (( data_read >> 9 ) & 0x01) )
					{
						printError( interruptReg.reg.DI1_INT, data_read );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI5_INT;
					}
					break;
				case 1:
					if( ((data_read_opt >> 0x1) & 0x1) != 1)
					{
						printError( 1, data_read_opt );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI6_INT;
					}

					if( interruptReg.reg.DI6_INT != ( ( data_read >> 2 )& 0x01) )
					{
						printError( interruptReg.reg.DI1_INT, data_read );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI6_INT;
					}
					break;
				case 2:
					if( ((data_read_opt >> 0x2) & 0x1) != 1)
					{
						printError( 1, data_read_opt );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI7_INT;
					}

					if( interruptReg.reg.DI7_INT != (( data_read >> 7 ) & 0x01) )
					{
						printError( interruptReg.reg.DI1_INT, data_read );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI7_INT;

					}
					break;
				case 3:
					if( ((data_read_opt >> 0x3) & 0x1) != 1)
					{
						printError( 1, data_read_opt );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI8_INT;
					}

					if( interruptReg.reg.DI8_INT != (( data_read >> 10) & 0x01) )
					{
						printError( interruptReg.reg.DI1_INT, data_read );
						//return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI8_INT;
					}
					break;
				case 4:
					if( ((data_read_opt >> 0x8) & 0x1) != 1)
					{
						printError( 1, data_read_opt );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI9_INT;
					}

					if( interruptReg.reg.DI9_INT != (( data_read >> 15) & 0x01) )
					{
						printError( interruptReg.reg.DI1_INT, data_read );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI9_INT;
					}
					break;
				case 5:
					if( ((data_read_opt >> 0x9) & 0x1) != 1)
					{
						printError( 1, data_read_opt );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI10_INT;
					}


					if( interruptReg.reg.DI10_INT != (( data_read >> 1) & 0x01) )
					{
						printError( interruptReg.reg.DI10_INT, data_read );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI10_INT;
					}
					break;
				case 6:
					if( ((data_read_opt >> 0xA) & 0x1) != 1)
					{
						printError( 1, data_read_opt );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI11_INT;
					}


					if( interruptReg.reg.DI11_INT != (( data_read >> 6) & 0x01) )
					{
						printError( interruptReg.reg.DI11_INT, data_read );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI11_INT;
					}
					break;
				case 7:
					if( ((data_read_opt >> 0xB) & 0x1) != 1)
					{
						printError( 1, data_read_opt );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI12_INT;
					}

					if( interruptReg.reg.DI12_INT != (data_read  & 0x01) )
					{
						printError( interruptReg.reg.DI12_INT, data_read );
						return ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI12_INT;
					}
					break;
			}

			discreteReg.raw32 <<=1;
			data_read = 0;
		}

	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End Test Discrete Input***");

	return TEST_OK;
}

void Discrete_Input::printError(UINT32 expected, UINT32 read)
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
