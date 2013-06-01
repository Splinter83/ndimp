/*
 * SIMPLoopbackCHASideB.cpp
 *
 *  Created on: 22/nov/2012
 *      Author: galileo
 */

#include "SIMPLoopbackCHASideB.h"


#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Loopback_Esterno.h"
#include "Logger.h"
#include "GlobalTypes.h"

SIMP_Loopback_CH_A_Side_B::SIMP_Loopback_CH_A_Side_B() {
	HS_CONTROL_BLOCK.ACTION_WORD = 0x0081;
	HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS = 0x0780;
	HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS = 0x1000;
	HS_CONTROL_BLOCK.PREAMBLE_S_B_WORD = 0x0028;
	HS_CONTROL_BLOCK.S_E_DELIMITER_FORMAT = 0x8E71;
	HS_CONTROL_BLOCK.BITE_DATA_ADDRESS = 0x0674;
	HS_MID_CW_DT_UNION.raw[LOW] = 0x3;
	HS_MID_CW_DT_UNION.raw[HIGH] = 0x0;
	RESTART_HS.RESTART_HS = 0x0000;
}

SIMP_Loopback_CH_A_Side_B::~SIMP_Loopback_CH_A_Side_B() {
	// TODO Auto-generated destructor stub
}

UINT8 SIMP_Loopback_CH_A_Side_B::execTest(const BoardInterfaceType& bt, int num_argomenti, ...) {

	va_list argP;
	va_start(argP, num_argomenti);
	int step = va_arg(argP, int);
	va_end(argP);

	UINT32 BASE_ADDRESS =
			GlobalData::instance()->GetInterfaceData(bt)->base_address;

	if (step == 1) {

		//Clear Memory
		for (UINT32 offset = 0;
				offset
						< GlobalData::instance()->GetInterfaceData(bt)->memory_size;
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
		vmeDev->write(
				BASE_ADDRESS + HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS * 2,
				HS_MID_CW_DT_UNION.raw[LOW]);

		// read hs last action word

		vmeDev->read(BASE_ADDRESS + LAST_ACTION_WORD_OFFSET,
				HS_LAST_ACTION_WORD_READ);

		if (HS_LAST_ACTION_WORD_READ != 0x0000) {
			snprintf(this->strError, MAX_BUF_SIZE, "Error during Loopback:\n"
					"The expected value for the HS Last Action Word is  0x%04x,"
					"while the read value is 0x%04x",
					HS_CONTROL_BLOCK.ACTION_WORD, HS_STATUS_WORD_READ);
			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: HS LAST ACTION WORD: the value expected was 4081, the value read is %x***",
					HS_LAST_ACTION_WORD_READ);
			return ERR_LOOP_LAST_ACTION_WORD;
		}

		vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->restart_hs,
				RESTART_HS.RESTART_HS);

		usleep(MSEC_TO_USEC(5));

		I_TEST *iTest = new Loopback_Esterno();
		iTest->setDevice(this->vmeDev);
		UINT8 res = TEST_NOK;
		if(strcmp(GlobalData::instance()->GetInterfaceData(bt)->board_name,"SIMP1") == 0){
			res = iTest->execTest(SIMP1_AVIONIC_3910,2, 'b',true);
		}
		else if (strcmp(GlobalData::instance()->GetInterfaceData(bt)->board_name,"SIMP2") == 0){
			res = iTest->execTest(SIMP2_ATTACK_3910,2, 'b',true);
		}

		if(res >= TEST_NOK){
			snprintf(this->strError, MAX_BUF_SIZE,
					"Error during External Loopback Channel: B\n"
					"Programming Loopback Channel B side A fail: %s",iTest->getError());
			delete iTest;
			return TEST_NOK;
		}
		delete iTest;
		return NEXT_STEP;
	} else if (step == 2) {
		vmeDev->read(BASE_ADDRESS + HS_STATUS_WORD_OFFSET, HS_STATUS_WORD_READ);
		if (HS_STATUS_WORD_READ != 0x0000) {
			snprintf(this->strError, MAX_BUF_SIZE,
					"Error during External Loopback side B Channel: A\n"
							"The expected value for the HS Status Word is 0x0000,"
							"while the read value is 0x%04x",
					HS_STATUS_WORD_READ);
			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: HS STATUS WORD: the value expected was 0000, the value read is %x***",
					HS_STATUS_WORD_READ);
			return ERR_LOOP_STATUS_WORD;
		}
		vmeDev->read(BASE_ADDRESS + HS_BIT_WORD_OFFSET, HS_BIT_WORD_READ);
		if (HS_BIT_WORD_READ != 0x0000) {
			snprintf(this->strError, MAX_BUF_SIZE,
					"Error during External side B Channel: A\n"
							"The expected value for the HS BIT Word is 0x0000,"
							"while the read value is 0x%04x",
					HS_BIT_WORD_READ);
			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: HS BIT WORD: the value expected was 0000, the value read is %x***",
					HS_BIT_WORD_READ);
			return ERR_LOOP_BIT_WORD;
		}

		// read hs last action word

		vmeDev->read(BASE_ADDRESS + LAST_ACTION_WORD_OFFSET,
				HS_LAST_ACTION_WORD_READ);

		if (HS_LAST_ACTION_WORD_READ != HS_CONTROL_BLOCK.ACTION_WORD) {
			snprintf(this->strError, MAX_BUF_SIZE, "Error during Loopback side B Channel: A:\n"
					"The expected value for the HS Last Action Word is  0x%04x,"
					"while the read value is 0x%04x", HS_CONTROL_BLOCK.ACTION_WORD,
					HS_STATUS_WORD_READ);
			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: HS LAST ACTION WORD: the value expected was 4081, the value read is %x***",
					HS_LAST_ACTION_WORD_READ);
			return ERR_LOOP_LAST_ACTION_WORD;
		}

		// read interrupt pointer number

		vmeDev->read(BASE_ADDRESS + HS_POINTER_NUM_OFFSET, HS_PTR_OFFSET_READ);

		vmeDev->read(BASE_ADDRESS + INTERRUPT_QUEUE_AREA + (HS_PTR_OFFSET_READ<<1)*2, INTERRUPT_WORD_1_READ);

		// potrebbe essere 0x4081

		if (INTERRUPT_WORD_1_READ != HS_CONTROL_BLOCK.ACTION_WORD) {
			UINT16 word;
			for(int indx = 0; indx < 64; ++indx){
				vmeDev->read(BASE_ADDRESS + INTERRUPT_QUEUE_AREA + indx*2,(UINT32&)word);
				Logger::getLogger()->Log(DEBUG_LEVEL, "Intterrupt word %d = 0x%04x",indx, word);
			}

			snprintf(this->strError, MAX_BUF_SIZE,
					"Error during External Loopback side B Channel: A\n"
							"The expected value for the HS Interrupt Status Word is 0x%04x,"
							"while the read value is 0x%04x",
					HS_CONTROL_BLOCK.ACTION_WORD, INTERRUPT_WORD_1_READ);

			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: INTERRUPT WORD 1: the value expected was %x, the value read is %x***",
					HS_CONTROL_BLOCK.ACTION_WORD, INTERRUPT_WORD_1_READ);


			return ERR_LOOP_INTERRUPT_WORD;
		}

		Logger::getLogger()->Log(INFO_LEVEL, "***End Loopback Esterno***");

	}

	return TEST_OK;
}

