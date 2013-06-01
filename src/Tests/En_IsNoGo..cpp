/*
 * En_IsNoGo..cpp
 *
 *  Created on: 27/nov/2012
 *      Author: savino
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "En_IsNoGo.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

En_IsNoGo::En_IsNoGo()
{
}

UINT8 En_IsNoGo::execTest(const BoardInterfaceType& bt,int num_argomenti, ...)
{
	Logger::getLogger()->Log(INFO_LEVEL, "***Start En_IsNoGo***");

	UINT32 DIRECT_IO = GlobalData::instance()->GetInterfaceData(bt)->direct_io;

	if( bt == STIMP_AVIONIC_3910)
	{
		IS_NOGO_RW_REG = DIRECT_IO + AVIONIC_ADDR + 0xC;
		IS_NOGO_WORD_RESET_REG = DIRECT_IO + AVIONIC_ADDR + 0xE;
	}
	else
	{

		IS_NOGO_RW_REG = DIRECT_IO + ATTACK_ADDR + 0xC;
		IS_NOGO_WORD_RESET_REG = DIRECT_IO + ATTACK_ADDR + 0xE;
	}


	//MCL
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0x1);
	usleep(MSEC_TO_USEC(500));

	//TEST
	vmeDev->read(IS_NOGO_RW_REG, flagReg);

	INOGO = (flagReg >> 0xA) & 0x1;
	if( INOGO != 0 )
	{

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag INOGO: the value expected was 0, the value read is %x***",
				INOGO);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag INOGO: the value expected was 0, the value read is %x***.",
				INOGO);

		return ERR_READ_INOGO;
	}


	//SET
	vmeDev->write(IS_NOGO_RW_REG, 0x1);

	usleep(MSEC_TO_USEC(500));

	//TEST
	vmeDev->read(IS_NOGO_RW_REG, flagReg);

	INOGO = (flagReg >> 0xA) & 0x1;
	if( INOGO != 1 )
	{

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag INOGO: the value expected was 1, the value read is %x***",
				INOGO);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag INOGO: the value expected was 1, the value read is %x***.",
				INOGO);

		return ERR_WRITE_INOGO;
	}


	//RESET
	vmeDev->write(IS_NOGO_WORD_RESET_REG, 0x01);

	usleep(MSEC_TO_USEC(500));

	//TEST
	vmeDev->read(IS_NOGO_RW_REG, flagReg);

	INOGO = (flagReg >> 0xA) & 0x1;
	if( INOGO != 0 )
	{

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag INOGO: the value expected was 0, the value read is %x***",
				INOGO);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag INOGO: the value expected was 0, the value read is %x***.",
				INOGO);


		return ERR_RESET_INOGO;
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End En_IsNoGo***");

	return TEST_OK;
}

