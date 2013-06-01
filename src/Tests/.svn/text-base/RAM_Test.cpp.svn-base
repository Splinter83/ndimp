/*
 * RAM_Test.cpp
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "RAM_Test.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"

RAM_Test::RAM_Test() {

}

UINT8 RAM_Test::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start RAM Test***");

/*	va_list argP;
	va_start(argP, num_argomenti);
	va_end(argP);
*/


	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	for (UINT32 i = 0; i < GlobalData::instance()->GetInterfaceData(bt)->memory_size; i+=2) {
		vmeDev->write(BASE_ADDRESS + i, ~(i),
				EN_VME_WORD);
	}

	//usleep(MSEC_TO_USEC(500));

	for (UINT32 i = 0; i < GlobalData::instance()->GetInterfaceData(bt)->memory_size; i+=2) {
		vmeDev->read(BASE_ADDRESS +  i, word_read, EN_VME_WORD);
		if (word_read != ((~ i) & 0xFFFF)) {
			snprintf(this->strError,MAX_BUF_SIZE,"Error during RAM Test:\n"
					"The expected value at address 0x%08x is 0x%04x,"
					"while the read value is 0x%04x", BASE_ADDRESS +  i, ((~ i) & 0xFFFF), word_read);

			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: RAM Test: the value expected at address %x was %x, the value read is %x***",
					BASE_ADDRESS + i, (~ i) & 0xFFFF,
					word_read);
			return ERR_RAM_COMPL;
		}
	}

	//usleep(MSEC_TO_USEC(500));

	UINT8 toggle = 0;
	for (UINT32 i = 0; i < (GlobalData::instance()->GetInterfaceData(bt)->memory_size); i+=2) {
		if (toggle % 2 == 0) {
			vmeDev->write(BASE_ADDRESS + i, 0x0000, EN_VME_WORD);
		} else {
			vmeDev->write(BASE_ADDRESS + i, 0xFFFF, EN_VME_WORD);
		}
		++toggle;
	}

	//usleep(MSEC_TO_USEC(500));

	toggle = 0;
	for (UINT32 i = 0; i < (GlobalData::instance()->GetInterfaceData(bt)->memory_size); i+=2) {
		vmeDev->read(BASE_ADDRESS + i, word_read, EN_VME_WORD);
		if (toggle % 2 == 0) {
			if (word_read != 0x0000) {
				snprintf(this->strError,MAX_BUF_SIZE,"Error during RAM Test:\n"
						"The expected value at address 0x%08x is 0x0000,"
						"while the read value is 0x%04x", BASE_ADDRESS +  i, word_read);
				Logger::getLogger()->Log(INFO_LEVEL,
						"***Error: RAM Test: the value expected at address %x was %x, the value read is %x***",
						BASE_ADDRESS + i, 0x0000, word_read);
				return ERR_RAM_TOGGLE;
			}
		} else {
			if (word_read != 0xFFFF) {
				snprintf(this->strError,MAX_BUF_SIZE,"Error during RAM Test:\n"
						"The expected value at address 0x%08x is 0xffff,"
						"while the read value is 0x%04x", BASE_ADDRESS +  i, word_read);
				Logger::getLogger()->Log(INFO_LEVEL,
						"***Error: RAM Test: the value expected at address %x was %x, the value read is %x***",
						BASE_ADDRESS + i, 0xFFFF, word_read);
				return ERR_RAM_TOGGLE;
			}
		}
		++toggle;
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End RAM Test***");

	return 0;
}

