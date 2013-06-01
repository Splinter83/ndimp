/*
 * ModNogo.cpp
 *
 *  Created on: 27/nov/2012
 *      Author: savino
 */


#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "ModNogo.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

Mod_Nogo::Mod_Nogo() {
	// TODO Auto-generated constructor stub
	MOD_NOGO_WORD_WRITE_REG = 0x28C80000;
	MOD_NOGO_WORD_RESET_REG = 0x28C00000;
}


UINT8 Mod_Nogo::execTest(const BoardInterfaceType& bt,int num_argomenti, ...)
{
	Logger::getLogger()->Log(INFO_LEVEL, "***Start Mod_Nogo***");

	UINT32 DIRECT_IO = GlobalData::instance()->GetInterfaceData(bt)->direct_io;

	if( bt == STIMP_AVIONIC_3910)
		MOD_NOGO_WORD_READ_REG = DIRECT_IO + AVIONIC_ADDR + 0xC;
	else
		MOD_NOGO_WORD_READ_REG = DIRECT_IO + ATTACK_ADDR + 0xC;


	//MCL
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0x1);
	usleep(MSEC_TO_USEC(500));

	//TEST
	vmeDev->read(MOD_NOGO_WORD_READ_REG, flagReg);

	MNOGO = (flagReg >> 0xB) & 0x1;
	if( MNOGO != 0 )
	{

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag MNOGO: the value expected was 0, the value read is %x***",
				MNOGO);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag MNOGO: the value expected was 0, the value read is %x***.",
				MNOGO);

		return ERR_READ_MOD;
	}


	//SET
	vmeDev->write(MOD_NOGO_WORD_WRITE_REG, 0x01);


	usleep(MSEC_TO_USEC(500));


	//TEST
	vmeDev->read(MOD_NOGO_WORD_READ_REG, flagReg);

	MNOGO = (flagReg >> 0xB) & 0x1;
	if( MNOGO != 1 )
	{

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag MNOGO: the value expected was 1, the value read is %x***",
				MNOGO);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag MNOGO: the value expected was 1, the value read is %x***.",
				MNOGO);

		return ERR_WRITE_MOD;
	}


	//RESET
	vmeDev->write(MOD_NOGO_WORD_RESET_REG, 0x01);

	usleep(MSEC_TO_USEC(500));

	//TEST
	vmeDev->read(MOD_NOGO_WORD_READ_REG, flagReg);

	MNOGO = (flagReg >> 0xB) & 0x1;
	if( MNOGO != 0 )
	{

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag INOGO: the value expected was 0, the value read is %x***",
				MNOGO);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag INOGO: the value expected was 0, the value read is %x***.",
				MNOGO);

		return ERR_RESET_MOD;
	}


	Logger::getLogger()->Log(INFO_LEVEL, "***End Mod_Nogo***");

	return TEST_OK;
}


