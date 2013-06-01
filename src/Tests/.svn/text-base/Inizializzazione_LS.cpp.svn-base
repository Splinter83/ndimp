/*
 * Inizializzazione_LS.cpp
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include "Inizializzazione_LS.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"

Inizializzazione_LS::Inizializzazione_LS() {
	CONTROL_BLOCK_POINTER_WRITE = 0x00A8;
	PROGRAM_POINTER_WRITE = 0x0000;
	RT_ICW_UNION.raw[LOW] = 0x0;
	RT_ICW_UNION.raw[HIGH] = 0x0;
	LS_RT_CONTROL_BLOCK.BASE_ADDRESS = 0x00B4;
}

UINT8 Inizializzazione_LS::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Inizializzazione LS***");

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	vmeDev->write(BASE_ADDRESS + CB_POINTER_OFFSET,
			CONTROL_BLOCK_POINTER_WRITE);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_OFFSET,
			PROGRAM_POINTER_WRITE);
	vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + 0xA,
			0xC000);
	vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + LS_RT_INTERFACE_CONTROL_WORD_OFFSET,
			RT_ICW_UNION.raw[LOW] + (RT_ICW_UNION.raw[HIGH] << 8));
	vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + LS_RT_BASE_ADDRESS_WORD_OFFSET,
			LS_RT_CONTROL_BLOCK.BASE_ADDRESS);
	vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + LS_RT_COMMAND_WORD_LIST_POINTER,0x300);

	Logger::getLogger()->Log(INFO_LEVEL, "***End Inizializzazione LS***");

	return TEST_OK;

}



