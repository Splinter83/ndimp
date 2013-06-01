/*
 * Selftest.cpp
 *
 *  Created on: 08/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Selftest.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"


#define BLOCK_8K_SIZE 0x2000

enum EN_ERROR_LS_SELFTEST{
	ERR_LS_STATUS_WORD = TEST_CUSTOM_ERR,
	ERR_LS_BITE_WORD,
	ERR_LS_RAM_BLOCK_INDEX
};

Selftest::Selftest() {
	CONTROL_BLOCK_POINTER_WRITE = 0x0140;
	PROGRAM_POINTER_WRITE = 0x0000;
	RT_ICW_UNION.raw[LOW] = 0x0;
	RT_ICW_UNION.raw[HIGH] = 0x1;
	SELFTEST_PROCEDURE_MASK_WRITE = 0x1FFF;
	RESTART_LS_WRITE = 0x0001;

}

UINT8 Selftest::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Selftest***");

/*	va_list argP;
	va_start(argP, num_argomenti);
	int i = va_arg(argP, int);
	va_end(argP);
*/
	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	//Clear Memory
	for (UINT32 i = 0; i < GlobalData::instance()->GetInterfaceData(bt)->memory_size; i+=2) {
		vmeDev->write(BASE_ADDRESS + i, 0x0);
	}

	vmeDev->write(BASE_ADDRESS + CB_POINTER_OFFSET,
			CONTROL_BLOCK_POINTER_WRITE);
	vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_OFFSET, PROGRAM_POINTER_WRITE);
	//Write Interface Control Word
	vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE * 2,ICW_SELFTEST_VALUE);
	vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE * 2 + SELFTEST_PROCEURE_MASK_OFFSET,
			SELFTEST_PROCEDURE_MASK_WRITE);
	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io, RESTART_LS_WRITE);

	usleep(SEC_TO_USEC(2));

	vmeDev->read(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE * 2 + INTERFACE_STATUS_WORD_OFFSET,
			INTERFACE_STATUS_WORD_READ);
	if (INTERFACE_STATUS_WORD_READ != 0x0020) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during LS Selftest:\n"
				"The expected value for the Interface Status Word is 0x0020,"
				"while the read value is 0x%04x", INTERFACE_STATUS_WORD_READ);

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: INTERFACE STATUS WORD: the value expected was 0020, the value read is %x***",
				INTERFACE_STATUS_WORD_READ);
		return ERR_LS_STATUS_WORD;
	}
	vmeDev->read(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE * 2 + LS_RT_ERROR_BITE_WORD_OFFSET,
			LS_RT_ERROR_BITE_WORD_READ);
	if (LS_RT_ERROR_BITE_WORD_READ != 0x0000) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during LS Selftest:\n"
				"The expected value for the Error/BITE word is 0x0000,"
				"while the read value is 0x%04x", LS_RT_ERROR_BITE_WORD_READ);
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: LS RT ERROR BITE WORD: the value expected was 0000, the value read is %x***",
				LS_RT_ERROR_BITE_WORD_READ);
		return ERR_LS_BITE_WORD;
	}

	UINT16 ramBlock = GlobalData::instance()->GetInterfaceData(bt)->memory_size / BLOCK_8K_SIZE;


	ramBlock = (1 << ramBlock) - 1;

	vmeDev->read(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE * 2 + LS_RT_RAM_BLOCK_INDEX_OFFSET,
			LS_RT_RAM_BLOCK_INDEX_READ);
	if (LS_RT_RAM_BLOCK_INDEX_READ != ramBlock) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during LS Selftest:\n"
				"The expected value for the RAM Block Index word is 0x%04x,"
				"while the read value is 0x%04x", ramBlock, LS_RT_RAM_BLOCK_INDEX_READ);

		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: LS RT RAM BLOCK INDEX: the value expected was 00FF, the value read is %x***",
				LS_RT_RAM_BLOCK_INDEX_READ);
		return ERR_LS_RAM_BLOCK_INDEX;
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End Selftest***");

	return TEST_OK;
}

