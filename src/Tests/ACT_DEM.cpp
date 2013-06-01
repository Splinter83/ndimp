/*
 * ACT_DEM.cpp
 *
 *  Created on: 12/set/2012
 *      Author: grande, savino(27/11/12)
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "ACT_DEM.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

ACT_DEM::ACT_DEM() {

}

UINT8 ACT_DEM::execTest(const BoardInterfaceType& bt, int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start ACT DEM***");

//	va_list argP;
//	va_start(argP, num_argomenti);
//	int step = va_arg(argP, int);
//	va_end(argP);

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;
	UINT32 DIRECT_IO = GlobalData::instance()->GetInterfaceData(bt)->direct_io;

	//GeneralConfigReg generalConf;
	//vmeDev->readConf(VME_GENERAL_CONF_ADDRESS, generalConf.raw32);

	if( bt == STIMP_AVIONIC_3910)
	{
		HANDOVER_STATUS_WORD_REG  = DIRECT_IO + AVIONIC_ADDR  + 0x8;
		HANDOVER_CONTROL_WORD_REG = DIRECT_IO + AVIONIC_ADDR ;
		HANDOVER_MINOR_LOOP_TIMER = DIRECT_IO + AVIONIC_ADDR + 0xA;
		PATTERN = 0x5;
	}
	else
	{
		HANDOVER_STATUS_WORD_REG  = DIRECT_IO + ATTACK_ADDR + 0x8;
		HANDOVER_CONTROL_WORD_REG = DIRECT_IO + ATTACK_ADDR;
		HANDOVER_MINOR_LOOP_TIMER = DIRECT_IO + ATTACK_ADDR + 0xA;
		PATTERN = 0xA;
	}

	//MCL
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0x1);
	usleep(MSEC_TO_USEC(500));

	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_HANDOVER_REG", hexadecimal),0x100);

	//Timer
	vmeDev->write(HANDOVER_MINOR_LOOP_TIMER, 0xFFC3);


	//SET
	vmeDev->write(HANDOVER_CONTROL_WORD_REG, 0x1C3);

	//TEST
	vmeDev->read(HANDOVER_STATUS_WORD_REG, BC_STATUS_WORD_READ);

	ACT = BC_STATUS_WORD_READ & 0x1;

	if(ACT != 1) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag ACT: the value expected was 1, the value read is %x***",
				ACT);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag ACT: the value expected was 1, the value read is %x***",
				ACT);

		return ERR_ACT;
	}

	DEM = (BC_STATUS_WORD_READ >> 0x1 ) & 0x1;
	if(DEM != 1) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag DEM: the value expected was 1, the value read is %x***",
				DEM);
		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag DEM: the value expected was 1, the value read is %x***",
				DEM);

		return ERR_DEM;
	}

	usleep(MSEC_TO_USEC(100));

	UINT32 data_read;
	vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_HANDOVER_REG", hexadecimal), data_read);


	if( (data_read & PATTERN) != PATTERN )
	{
		Logger::getLogger()->Log(INFO_LEVEL,
						"***Error: flag ACT DEM: the value expected was 0xF, the value read is %x***",
						data_read);
		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag ACT DEM: the value expected was 0xF, the value read is %x***",
				data_read);

		return ERR_ACTDEM_FLAG;

	}

	//SET
	//vmeDev->write(HANDOVER_CONTROL_WORD_REG, 0x0);

	Logger::getLogger()->Log(INFO_LEVEL, "***End ACT DEM***");

	return TEST_OK;
}




