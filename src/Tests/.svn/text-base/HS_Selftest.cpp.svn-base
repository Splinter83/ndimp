/*
 * HS_Selftest.cpp
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "HS_Selftest.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"

HS_Selftest::HS_Selftest() {
	HS_CONTROL_BLOCK.ACTION_WORD = 0x4081;
	//HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS = 0x4004;
    HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS = 0x1010;
	//HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS = 0x834;
    HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS = 0x1000;
	//HS_CONTROL_BLOCK.PREAMBLE_S_B_WORD = 0xC128;
    HS_CONTROL_BLOCK.PREAMBLE_S_B_WORD = 0x8028;
	HS_CONTROL_BLOCK.S_E_DELIMITER_FORMAT = 0x8E71;
	//HS_CONTROL_BLOCK.BITE_DATA_ADDRESS = 0xEF4;
    HS_CONTROL_BLOCK.BITE_DATA_ADDRESS = 0x0674;
	HS_MID_CW_ST_UNION.raw[LOW] = 0x3;
	HS_MID_CW_ST_UNION.raw[HIGH] = 0x0;
	HS_BITE_BUFFER.INFO_TX_DATA = 0x5A3C;
	HS_BITE_BUFFER.INFO_RX_DATA = 0x0000;
	RESTART_HS.RESTART_HS = 0x0000;
}

UINT8 HS_Selftest::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {
	UINT32 DATA_RX_READ;
	UINT16 currentPointerNumOffset;
	Logger::getLogger()->Log(INFO_LEVEL, "***Start HS Selftest***");

/*	va_list argP;
	va_start(argP, num_argomenti);
	va_end(argP);
*/


	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	vmeDev->read(BASE_ADDRESS + HS_POINTER_NUM_OFFSET,
			(UINT32&)currentPointerNumOffset);

	//Clear Memory
	for (UINT32 offset = 0;
			offset < GlobalData::instance()->GetInterfaceData(bt)->memory_size;
			offset += 2) {
		vmeDev->write(BASE_ADDRESS + offset, 0x0);
	}

	vmeDev->write(BASE_ADDRESS, HS_CONTROL_BLOCK.ACTION_WORD);
	vmeDev->write(BASE_ADDRESS + EFFECTIVE_DATA_ADDRESS_OFFSET,
			HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS);
	vmeDev->write(BASE_ADDRESS + TABLE_POINTER_ADDRESS_OFFSET,
			HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS);
	vmeDev->write(BASE_ADDRESS + PRSIZE_WORD_OFFSET,
			HS_CONTROL_BLOCK.PREAMBLE_S_B_WORD);
	vmeDev->write(BASE_ADDRESS + START_END_DELIMITER_FORMAT_OFFSET,
			HS_CONTROL_BLOCK.S_E_DELIMITER_FORMAT);
	vmeDev->write(BASE_ADDRESS + BITE_DATA_ADDRESS_OFFSET,
			HS_CONTROL_BLOCK.BITE_DATA_ADDRESS);

    vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS * 2),
			0x1010);
    vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS * 2),
			0x0000);

	vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.BITE_DATA_ADDRESS * 2), HS_MID_CW_ST_UNION.raw[LOW]);
	vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.BITE_DATA_ADDRESS * 2) + DATA_TX_OFFSET,
			HS_BITE_BUFFER.INFO_TX_DATA);
	vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.BITE_DATA_ADDRESS * 2) + DATA_RX_OFFSET,
			HS_BITE_BUFFER.INFO_RX_DATA);

    // leggere HS LAST ACTION WORD
    vmeDev->read(BASE_ADDRESS + LAST_ACTION_WORD_OFFSET,HS_LAST_ACTION_WORD_READ);

	if (HS_LAST_ACTION_WORD_READ != 0x0000) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Selftest:\n"
				"The expected value for the HS Last Action Word is  0x0000,"
				"while the read value is 0x%04x", HS_LAST_ACTION_WORD_READ);
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: HS LAST ACTION WORD: the value expected was 4081, the value read is %x***",
				HS_LAST_ACTION_WORD_READ);
		return ERR_HS_LAST_ACTION_WORD;
	}


	//Restart HS
	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->restart_hs, RESTART_HS.RESTART_HS);

	usleep(MSEC_TO_USEC(5));

	vmeDev->read(BASE_ADDRESS + HS_STATUS_WORD_OFFSET,
			HS_STATUS_WORD_READ);
	if (HS_STATUS_WORD_READ != 0x0000) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Selftest:\n"
				"The expected value for the HS Status Word is 0x0000,"
				"while the read value is 0x%04x", HS_STATUS_WORD_READ);
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: HS STATUS WORD: the value expected was 0000, the value read is %x***",
				HS_STATUS_WORD_READ);
		return ERR_HS_STATUS_WORD;
	}
	vmeDev->read(BASE_ADDRESS + LAST_ACTION_WORD_OFFSET,
			HS_LAST_ACTION_WORD_READ);
	if (HS_LAST_ACTION_WORD_READ != HS_CONTROL_BLOCK.ACTION_WORD) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Selftest:\n"
				"The expected value for the HS Last Action Word is  0x%04x,"
				"while the read value is 0x%04x",HS_CONTROL_BLOCK.ACTION_WORD, HS_STATUS_WORD_READ);
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: HS LAST ACTION WORD: the value expected was 4081, the value read is %x***",
				HS_LAST_ACTION_WORD_READ);
		return ERR_HS_LAST_ACTION_WORD;
	}
	vmeDev->read(BASE_ADDRESS + HS_BIT_WORD_OFFSET, HS_BIT_WORD_READ);
	if (HS_BIT_WORD_READ != 0x0000) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Selftest:\n"
				"The expected value for the HS BIT Word is 0x0000,"
				"while the read value is 0x%04x", HS_BIT_WORD_READ);
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: HS BIT WORD: the value expected was 0000, the value read is %x***",
				HS_BIT_WORD_READ);
		return ERR_HS_BIT_WORD;
	}
	vmeDev->read(BASE_ADDRESS + HS_POINTER_NUM_OFFSET,
			HS_PTR_OFFSET_READ);
	/*TODO
	 * Verify the correctness of Pointer offset number
	 * Expected value 0x01 ?!?!
	 */
	//if (HS_PTR_OFFSET_READ != 0x0000) {
/*    if ((HS_PTR_OFFSET_READ & 0xFFFF) != currentPointerNumOffset) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Selftest:\n"
				"The expected value for the HS Pointer Number is 0x%04x,"
				"while the read value is 0x%04x",currentPointerNumOffset, HS_PTR_OFFSET_READ);

		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: HS PTR OFFSET: the value expected was 0000, the value read is %x***",
				HS_PTR_OFFSET_READ);
		return ERR_HS_PNTR_NUM;
	}*/
	vmeDev->read(BASE_ADDRESS + INTERRUPT_QUEUE_AREA + (HS_PTR_OFFSET_READ<<1)*2,
			INTERRUPT_WORD_1_READ);
	/*TODO
	 * Verify the correctness of Interrupt Status Word value:
	 * Expected value 0x0803 ?!?!
	 */
	if (INTERRUPT_WORD_1_READ != HS_CONTROL_BLOCK.ACTION_WORD) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Selftest:\n"
				"The expected value for the HS Interrupt Status Word is 0x408C,"
				"while the read value is 0x%04x", INTERRUPT_WORD_1_READ);

		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: INTERRUPT WORD 1: the value expected was 408C, the value read is %x***",
				INTERRUPT_WORD_1_READ);
		return ERR_HS_INTERRUPT_WORD;
	}
	vmeDev->read(BASE_ADDRESS + (HS_CONTROL_BLOCK.BITE_DATA_ADDRESS * 2) + DATA_RX_OFFSET, DATA_RX_READ);
	if (DATA_RX_READ != 0x5A3C) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Selftest:\n"
				"The expected value for the HS Data RX is 0x5A3C,"
				"while the read value is 0x%04x", DATA_RX_READ);

		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: DATA RX: the value expected was 5A3C, the value read is %x***",
				DATA_RX_READ);

		return ERR_HS_DATA_RX;
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End HS Selftest***");

	return TEST_OK;
}




