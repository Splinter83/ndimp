/*
 * HS_Interrupt_Pointer_Offset.cpp
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "HS_Interrupt_Pointer_Offset.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"

HS_Interrupt_Pointer_Offset::HS_Interrupt_Pointer_Offset() {
	//HS_CONTROL_BLOCK.ACTION_WORD = 0x0080;
     HS_CONTROL_BLOCK.ACTION_WORD = 0x4081;
	//HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS = 0x4004;
    HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS = 0x1010;
	//HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS = 0x634;
    HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS = 0x1000;
    HS_CONTROL_BLOCK.HS_LAST_ACTION_WORD = 0x0000;
	//HS_CONTROL_BLOCK.PREAMBLE_S_B_WORD = 0x0028; /*TODO SELFTEST Disabled? */
    HS_CONTROL_BLOCK.PREAMBLE_S_B_WORD = 0x8028;
	HS_CONTROL_BLOCK.S_E_DELIMITER_FORMAT = 0x8E71;
	//HS_CONTROL_BLOCK.BITE_DATA_ADDRESS = 0xEF4;
    HS_CONTROL_BLOCK.BITE_DATA_ADDRESS = 0x674;
	HS_MID_CW_DT_UNION.raw[LOW] = 0x3;
	HS_MID_CW_DT_UNION.raw[HIGH] = 0x0;
    HS_BITE_BUFFER.INFO_TX_DATA = 0x5A3C;
	HS_BITE_BUFFER.INFO_RX_DATA = 0x0000;
	RESTART_HS.RESTART_HS = 0x0000;
}

UINT8 HS_Interrupt_Pointer_Offset::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL,
			"***Start Test HS Interrupt Pointer Offset***");

	UINT32 currentInterruptNum = 0;

/*	va_list argP;
	va_start(argP, num_argomenti);
	va_end(argP);*/
	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;
	//Clear Memory
	for (UINT32  offset = 0;
			offset	< GlobalData::instance()->GetInterfaceData(bt)->memory_size;
			offset += 2) {
		vmeDev->write(BASE_ADDRESS + offset, 0x0);
	}


	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	vmeDev->write(BASE_ADDRESS, HS_CONTROL_BLOCK.ACTION_WORD);

	vmeDev->write(BASE_ADDRESS + EFFECTIVE_DATA_ADDRESS_OFFSET,
			HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS);

	vmeDev->write(BASE_ADDRESS + TABLE_POINTER_ADDRESS_OFFSET,
			HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS);

    vmeDev->write(BASE_ADDRESS + LAST_ACTION_WORD_OFFSET, HS_CONTROL_BLOCK.HS_LAST_ACTION_WORD);

	vmeDev->write(BASE_ADDRESS + PRSIZE_WORD_OFFSET,
			HS_CONTROL_BLOCK.PREAMBLE_S_B_WORD);

	vmeDev->write(BASE_ADDRESS + START_END_DELIMITER_FORMAT_OFFSET,
			HS_CONTROL_BLOCK.S_E_DELIMITER_FORMAT);

	vmeDev->write(BASE_ADDRESS + BITE_DATA_ADDRESS_OFFSET,
			HS_CONTROL_BLOCK.BITE_DATA_ADDRESS);

	//vmeDev->write(BASE_ADDRESS + HS_WR_AR_BUFFER_TYPE_OFFSET,
	//		HS_MID_CW_DT_UNION.raw[LOW] + (HS_MID_CW_DT_UNION.raw[HIGH]));

    vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS * 2),
			HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS);

    vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS * 2),
			0x0000);

	vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.BITE_DATA_ADDRESS * 2), HS_MID_CW_DT_UNION.raw[LOW]);

	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->restart_hs, RESTART_HS.RESTART_HS);

        vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.BITE_DATA_ADDRESS * 2) + DATA_TX_OFFSET,
			HS_BITE_BUFFER.INFO_TX_DATA);

	vmeDev->write(BASE_ADDRESS + (HS_CONTROL_BLOCK.BITE_DATA_ADDRESS * 2) + DATA_RX_OFFSET,
			HS_BITE_BUFFER.INFO_RX_DATA);

	vmeDev->read(BASE_ADDRESS + HS_POINTER_NUM_OFFSET,
			currentInterruptNum);

	//Restart HS
	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->restart_hs, RESTART_HS.RESTART_HS);

	usleep(MSEC_TO_USEC(5));

	vmeDev->read(BASE_ADDRESS + LAST_ACTION_WORD_OFFSET,
			HS_LAST_ACTION_WORD_READ);
	if (HS_LAST_ACTION_WORD_READ != 0x4081) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Interrupt Pointer Offset Test: "
				"The expected value for the HS Last Action Word is 0x0080,while the read value is 0x%04x", HS_LAST_ACTION_WORD_READ);
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: HS LAST ACTION WORD: the value expected was 0080, the value read is %x***",
				HS_LAST_ACTION_WORD_READ);
		return ERR_LAST_ACTION_WORD;

	}
	vmeDev->read(BASE_ADDRESS + HS_POINTER_NUM_OFFSET,
			HS_PTR_OFFSET_READ);
	if (HS_PTR_OFFSET_READ != ++currentInterruptNum) {
		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Interrupt Pointer Offset Test: "
				"The expected value for the Interrupt Pointer Number is 0x%04x,while the read value is 0x%04x", currentInterruptNum, HS_PTR_OFFSET_READ);
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Error: HS PTR OFFSET: the value expected was 0000, the value read is %x***",
				HS_PTR_OFFSET_READ);
		return ERR_PNTR_NUM;
	}

	vmeDev->write(BASE_ADDRESS + LAST_ACTION_WORD_OFFSET, 0x0000);

	vmeDev->read(BASE_ADDRESS + HS_POINTER_NUM_OFFSET,
			currentInterruptNum);
	for (unsigned int i = 1; i <= 64; i++) {
		vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->restart_hs, RESTART_HS.RESTART_HS);

		vmeDev->read(BASE_ADDRESS + HS_POINTER_NUM_OFFSET,
				HS_PTR_OFFSET_READ);
		if (HS_PTR_OFFSET_READ != ((currentInterruptNum+i)%64)) {
			snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Interrupt Pointer Offset Test: "
					"The expected value for the Interrupt Pointer Number is 0x%4x,while the read value is 0x%04x",i, HS_PTR_OFFSET_READ);

			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: HS PTR OFFSET: the value expected was %x, the value read is %x***",
					i, HS_PTR_OFFSET_READ);
			return ERR_PNTR_NUM_COUNTER;
		}
	}

	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->restart_hs, RESTART_HS.RESTART_HS);

	vmeDev->read(BASE_ADDRESS + HS_POINTER_NUM_OFFSET,
			HS_PTR_OFFSET_READ);
//	if (HS_PTR_OFFSET_READ != 0x0) {
//		snprintf(this->strError,MAX_BUF_SIZE,"Error during HS Interrupt Pointer Offset Test: "
//				"The expected value for the Interrupt Pointer Number is 0x0000,while the read value is 0x%04x", HS_PTR_OFFSET_READ);
//
//		Logger::getLogger()->Log(DEBUG_LEVEL,
//				"***Error: HS PTR OFFSET: the value expected was 0000, the value read is %x***",
//				HS_PTR_OFFSET_READ);
//
//		return ERR_PNTR_NUM_END_LOOP;
//	}


	Logger::getLogger()->Log(INFO_LEVEL,
			"***End Test HS Interrupt Pointer Offset***");

	return TEST_OK;
}




