/*
 * Nmi_3909.cpp
 *
 *  Created on: 28/nov/2012
 *      Author: savino
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Nmi_3909.h"
#include "external_vars.h"
#include "Logger.h"
#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"


Nmi_3909::Nmi_3909() {
	// TODO Auto-generated constructor stub

}

Nmi_3909::~Nmi_3909() {
	// TODO Auto-generated destructor stub
}

UINT8 Nmi_3909::execTest(const BoardInterfaceType& bt,int num_argomenti, ...)
{

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Nmi_3909***");

	UINT32 DIRECT_IO = GlobalData::instance()->GetInterfaceData(bt)->direct_io;
	NMI_WORD_WRITE_REG = DIRECT_IO + 0xC0000;

	if( bt == STIMP_AVIONIC_3910)
	{
		NMI_WORD_READ_REG = DIRECT_IO + AVIONIC_ADDR + 0xC;
		NMI_WORD_RESET_REG = NMI_WORD_READ_REG;
	}
	else
	{
		NMI_WORD_READ_REG = DIRECT_IO + ATTACK_ADDR + 0xC;
		NMI_WORD_RESET_REG = NMI_WORD_READ_REG;
	}

	//MCL
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0x1);
	usleep(MSEC_TO_USEC(500));

	//TEST
	vmeDev->read(NMI_WORD_READ_REG, flagReg);

	NMI = (flagReg >> 0xD) & 0x1;
	if( NMI != 0 )
	{

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag NMI: the value expected was 0, the value read is %x***",
				NMI);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag NMI: the value expected was 0, the value read is %x***.",
				NMI);

		return ERR_READ_NMI;
	}


	//SET
	vmeDev->write(NMI_WORD_WRITE_REG, 0x01);
	usleep(MSEC_TO_USEC(500));


	//TEST
	vmeDev->read(NMI_WORD_READ_REG, flagReg);

	NMI = (flagReg >> 0xC) & 0x1;
	if( NMI != 1 )
	{

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag NMI: the value expected was 1, the value read is %x***",
				NMI);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag NMI: the value expected was 1, the value read is %x***.",
				NMI);

		return ERR_WRITE_NMI;
	}

	//MCL
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0x1);
	usleep(MSEC_TO_USEC(500));

	vmeDev->read(NMI_WORD_READ_REG, flagReg);

	NMI = (flagReg >> 0xC) & 0x1;
	if( NMI != 0 )
	{

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag NMI: the value expected was 0, the value read is %x***",
				NMI);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag NMI: the value expected was 0, the value read is %x***.",
				NMI);

		return ERR_RESET_NMI;
	}


	Logger::getLogger()->Log(INFO_LEVEL, "***End Nmi_3909***");

	return TEST_OK;
}

