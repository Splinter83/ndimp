/*
 * Verifica_Mod_BC.cpp
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include "Verifica_Mod_BC.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"

Verifica_Mod_BC::Verifica_Mod_BC() {

}

UINT8 Verifica_Mod_BC::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Verifica mod BC***");

/*	va_list argP;
	va_start(argP, num_argomenti);
	int i = va_arg(argP, int);
	va_end(argP);*/

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	vmeDev->read(BASE_ADDRESS + LS_BC_CONTROL_BLOCK_OFFSET + 0x6,
			ISW_READ);
	if (ISW_READ != 0xD280) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: INTERFACE STATUS WORD: the value expected was D280, the value read is %x***",
				ISW_READ);
		/** TODO
		 * SET ERROR
		 */
		return TEST_NOK;
	}
	vmeDev->read(BASE_ADDRESS + BC_QUEUE_TYPE_OFFSET,
			IAW1_READ);
	if (IAW1_READ != 0x0000) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: INSTRUCTION ADDRESS WORD 1: the value expected was 0000, the value read is %x***",
				IAW1_READ);
		/** TODO
		 * SET ERROR
		 */
		return TEST_NOK;
	}
	vmeDev->read(BASE_ADDRESS + BC_QUEUE_TYPE_OFFSET + 0x2,
			INSW1_READ);
	if (INSW1_READ != 0x8001) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: INSTRUCTION STATUS WORD 1: the value expected was 8001, the value read is %x***",
				INSW1_READ);
		/** TODO
		 * SET ERROR
		 */
		return TEST_NOK;
	}
	vmeDev->read(BASE_ADDRESS + BC_QUEUE_TYPE_OFFSET + 0x4,
			AW1_READ);
	if (AW1_READ != 0x0000) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: AUXILIARY WORD 1: the value expected was 0000, the value read is %x***",
				AW1_READ);
		/** TODO
		 * SET ERROR
		 */
		return TEST_NOK;
	}
	vmeDev->read(BASE_ADDRESS + BC_QUEUE_TYPE_OFFSET + 0x6,
			AW2_READ);
	if (AW2_READ != 0x0000) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: AUXILIARY WORD 2: the value expected was 0000, the value read is %x***",
				AW2_READ);
		/** TODO
		 * SET ERROR
		 */
		return TEST_NOK;
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End Verifica mod BC***");

	return TEST_OK;
}



