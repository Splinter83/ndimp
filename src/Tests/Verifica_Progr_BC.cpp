/*
 * Verifica_Progr_BC.cpp
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include "Verifica_Progr_BC.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"

Verifica_Progr_BC::Verifica_Progr_BC() {
	PROGRAM_POINTER_WRITE = 0x1000;
	RESTART_LS_WRITE = 0x0001;
}

UINT8 Verifica_Progr_BC::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Verifica Progr BC***");

/*	va_list argP;
	va_start(argP, num_argomenti);
	int i = va_arg(argP, int);
	va_end(argP);*/

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_OFFSET,
			PROGRAM_POINTER_WRITE);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2, 0x1C02);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x2, 0xFB51);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x4, 0x00CB);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x6, 0x1C02);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x8, 0xFB51);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0xA, 0x014B);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0xC, 0x4000);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0xE, 0x1000);
	vmeDev->write(BASE_ADDRESS + PRSIZE_WORD_OFFSET, 0x0028);
	vmeDev->write(BASE_ADDRESS + START_END_DELIMITER_FORMAT_OFFSET,
			0x8E71);

	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
			RESTART_LS_WRITE);
	usleep(MSEC_TO_USEC(5));

	Logger::getLogger()->Log(INFO_LEVEL, "***End Verifica Progr BC***");

	return TEST_OK;
}

