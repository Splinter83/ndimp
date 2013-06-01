/*
 * Program_BC.cpp
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Program_BC.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

#define INSTRUCTION_WORD_OFFSET 0xA // 5 word

Program_BC::Program_BC() {
	CONTROL_BLOCK_POINTER_WRITE = 0x00A0;
	PROGRAM_POINTER_WRITE = 0x0000;
	BC_ICW_UNION.raw[LOW] = 0x80;
	BC_ICW_UNION.raw[HIGH] = 0x02;
	LS_BC_CONTROL_BLOCK.BASE_ADDRESS = 0x0200;
	LS_BC_CONTROL_BLOCK.IAWLP = 0x0100;
	DATA_POINTER.ITF_DATA_PTR = 0x0500;
	RESTART_LS_WRITE = 0x0001;
}

UINT8 Program_BC::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Program BC***");
	UINT16 instruction_address_word1;
	UINT16 instruction_status_word1;
	UINT16 auxiliary_word;
	UINT32 INTERFACE_STATUS_WORD_READ;
	va_list argP;
	va_start(argP, num_argomenti);
	int step = va_arg(argP, int);
	va_end(argP);

	if(step == 1){

		BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

		//Clear Memory
		for (UINT32 offset = 0;
				offset < GlobalData::instance()->GetInterfaceData(bt)->memory_size;
				offset += 2) {
			vmeDev->write(BASE_ADDRESS + offset, 0x0);
		}

		vmeDev->write(BASE_ADDRESS + CB_POINTER_OFFSET,
				CONTROL_BLOCK_POINTER_WRITE);
		vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_OFFSET,
				PROGRAM_POINTER_WRITE);
		vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + LS_BC_CONTROL_BLOCK_OFFSET,
				0x200);
		vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + 0x2,
				LS_BC_CONTROL_BLOCK.BASE_ADDRESS);
		vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + 0x4,
				LS_BC_CONTROL_BLOCK.IAWLP);

		UINT16 offset = 0;
		//Fill first 10 I/F data pointer buffer with 0x0500 value
		for (UINT16 count = 0; count <10; ++count){
			vmeDev->write(BASE_ADDRESS + LS_BC_CONTROL_BLOCK.BASE_ADDRESS*2 + 0x4 + offset,
					DATA_POINTER.ITF_DATA_PTR);
			offset += 0x4; // moves forward 2 words (interface data pointer + host data pointer)
		}
		//MID CW (effective data address value *2, so it I/F Data Pointer value *2)
		//vmeDev->write(BASE_ADDRESS + DATA_POINTER.ITF_DATA_PTR*2, 0x0003);
		offset = 0;
		for (UINT32 count = 0; count <16; ++count){
			vmeDev->write(BASE_ADDRESS + DATA_POINTER.ITF_DATA_PTR*2 + offset,
					count);
			offset += 0x2; // moves forward 2 words (interface data pointer + host data pointer)
		}


		//Restart
		vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
				RESTART_LS_WRITE);
		usleep(MSEC_TO_USEC(2));

		vmeDev->read(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + INTERFACE_STATUS_WORD_OFFSET,
				INTERFACE_STATUS_WORD_READ);

		vmeDev->read(BASE_ADDRESS + LS_BC_CONTROL_BLOCK.IAWLP*2, (UINT32&)instruction_address_word1);
		if (instruction_address_word1 != 0x0000) {
			snprintf(this->strError,MAX_BUF_SIZE,"Error during BC Program: "
					"The expected value for the Instruction Address Word 1 is 0x0000,while the read value is 0x%04x", instruction_address_word1);

			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: BC Program: the value expected for IAW was 0x0000, the value read is %x***",
					instruction_address_word1);
			return ERR_BC_IAW;
		}


		vmeDev->read(BASE_ADDRESS + LS_BC_CONTROL_BLOCK.IAWLP*2 + 0x2, (UINT32&)instruction_status_word1);
		if (instruction_status_word1 != 0x8001) {
			snprintf(this->strError,MAX_BUF_SIZE,"Error during BC Program: "
					"The expected value for the Interface Status Word 1 is 0x0000,while the read value is 0x%04x", instruction_address_word1);

			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: BC Program: the value expected for ISW was 0x0000, the value read is %x***",
					instruction_status_word1);
			return ERR_BC_ISW;
		}

		//Word 1 A
		vmeDev->read(BASE_ADDRESS + LS_BC_CONTROL_BLOCK.IAWLP*2 + 0x4, (UINT32&)auxiliary_word);
		if (auxiliary_word != 0x0000) {
			snprintf(this->strError,MAX_BUF_SIZE,"Error during BC Program: "
					"The expected value for the Auxiliary Word 1 is 0x0000,while the read value is 0x%04x", auxiliary_word);

			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: BC Program: the value expected for AWA was 0x0000, the value read is %x***",
					auxiliary_word);
			return ERR_AUX_WORD_A;
		}

		//Word 1 B
		vmeDev->read(BASE_ADDRESS + LS_BC_CONTROL_BLOCK.IAWLP*2 + 0x6, (UINT32&)auxiliary_word);
		if (auxiliary_word != 0x0000) {
			snprintf(this->strError,MAX_BUF_SIZE,"Error during BC Program: "
					"The expected value for the Auxiliary Word 2 is 0x0000,while the read value is 0x%04x", auxiliary_word);

			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: BC Program: the value expected for AWB was 0x0000, the value read is %x***",
					auxiliary_word);
			return ERR_AUX_WORD_B;
		}

		//Test BC Programming
		PROGRAM_POINTER_WRITE = 0x1000;
		vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_OFFSET,
				PROGRAM_POINTER_WRITE);

		vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2, 0x1C02);
		vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x2, 0xF830);
		vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x4, 0x1E04);
		//vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x6, 0x1E02);
		vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x6, 0xF830);
		//vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0xA, 0x014B);
		vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x8, 0x4000);
		vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0xA, 0x1000);
		vmeDev->write(BASE_ADDRESS + PRSIZE_WORD_OFFSET, 0x0028);
		vmeDev->write(BASE_ADDRESS + START_END_DELIMITER_FORMAT_OFFSET,
				0x8E71);

		vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
				RESTART_LS_WRITE);
		usleep(MSEC_TO_USEC(5));
		return NEXT_STEP;

	}
	else if (step == 2){
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
		usleep(SEC_TO_USEC(2));
		//vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0x8, 0xD000);
		//vmeDev->write(BASE_ADDRESS + PROGRAM_POINTER_WRITE*2 + 0xA, 0x1000);
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End Program BC***");

	return TEST_OK;
}

