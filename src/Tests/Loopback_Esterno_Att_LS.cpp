/*
 * Loopback_Esterno_Att_LS.cpp
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Loopback_Esterno_Att_LS.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"

Loopback_Esterno_Att_LS::Loopback_Esterno_Att_LS() {
	CONTROL_BLOCK_POINTER_WRITE = 0x00A0;
	PROGRAM_POINTER_WRITE = 0x0000;
	RT_ICW_UNION.raw[LOW] = 0x00;
	RT_ICW_UNION.raw[HIGH] = 0x01;
	SELFTEST_PROCEDURE_MASK_WRITE = 0x1FFF; /*TODO Selftest disabled? */
	RESTART_LS_WRITE = 0x0001;
	HS_CONTROL_BLOCK.PREAMBLE_S_B_WORD = 0x228;
	HS_CONTROL_BLOCK.S_E_DELIMITER_FORMAT = 0x8E71;
	RT_ICW_UNION2.raw[LOW] = 0x80; //0x80;
	RT_ICW_UNION2.raw[HIGH] = 0x00;
	LS_RT_CONTROL_BLOCK.BASE_ADDRESS = 0x0200;
	HS_DESCRIPTOR_TABLE.NORM_PTR[0].ITF_DATA_PTR = 0x4000;
	HS_DESCRIPTOR_TABLE.NORM_PTR[0].HOST_DATA_PTR = 0x4000;
	SUBADDRESS_CONTROL_WORD_UNION.raw[LOW] = 0x0000;
	SUBADDRESS_CONTROL_WORD_UNION.raw[HIGH] = 0x0000;
	SUBADDRESS_DESCRIPTOR.ITF_DATA_PTR = 0x1000;
	SUBADDRESS_DESCRIPTOR.HOST_DATA_PTR = 0x1000;
	HS_MID_CW_DT_UNION.raw[LOW] = 0x00;
	HS_MID_CW_DT_UNION.raw[HIGH] = 0x00;
	HS_DATA_POINTER.ITF_DATA_PTR = 0x4000;
	HS_DATA_POINTER.HOST_DATA_PTR = 0x4000;
	HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS = 0x1000;
	HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS = 0x0780;
	HS_CONTROL_BLOCK.BITE_DATA_ADDRESS = 0x0674;
}

UINT8 Loopback_Esterno_Att_LS::execTest(const BoardInterfaceType& bt,
		int num_argomenti, ...) {
	char CH;
	const UINT16 sub_addr = 26;

	Logger::getLogger()->Log(INFO_LEVEL,
			"***Start Loopback Esterno Attivato da LS***");

	va_list argP;
	va_start(argP, num_argomenti);
	CH = va_arg(argP, int);
	int step = va_arg(argP, int);
	va_end(argP);

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;



	try {
		if (step == 1) {
			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Start Loopback Esterno Attivato da LS step 1***");

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
			vmeDev->write(
					BASE_ADDRESS
							+ CONTROL_BLOCK_POINTER_WRITE*2 +
								LS_RT_INTERFACE_CONTROL_WORD_OFFSET,
					RT_ICW_UNION.raw[LOW] + (RT_ICW_UNION.raw[HIGH] << 8));
			vmeDev->write(
					BASE_ADDRESS
							+ CONTROL_BLOCK_POINTER_WRITE*2 +
								LS_RT_SELFTEST_PROCEDURE_MASK_OFFSET,
					SELFTEST_PROCEDURE_MASK_WRITE);

			//Restart
			vmeDev->write(
					GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
					RESTART_LS_WRITE);

			usleep(SEC_TO_USEC(2));

			vmeDev->read(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + INTERFACE_STATUS_WORD_OFFSET,
					INTERFACE_STATUS_WORD_READ);
			if (INTERFACE_STATUS_WORD_READ != 0x0020) {
				snprintf(this->strError, MAX_BUF_SIZE,
						"Error during External Loopback Channel %c activated by LS:\n"
								"The expected value for the Interface Status Word is 0x0020,"
								"while the read value is 0x%04x", CH - 32,
						INTERFACE_STATUS_WORD_READ);
				Logger::getLogger()->Log(DEBUG_LEVEL,
						"***Error: INTERFACE STATUS WORD: the value expected was 0020, the value read is %x***",
						INTERFACE_STATUS_WORD_READ);
				return ERR_LOOP_LS_INT_STATUS_WORD;
			}

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
			vmeDev->write(
					BASE_ADDRESS
							+ CONTROL_BLOCK_POINTER_WRITE*2 + LS_RT_INTERFACE_CONTROL_WORD_OFFSET,
					0x80 );
					//		RT_ICW_UNION2.raw[LOW] + (RT_ICW_UNION2.raw[HIGH] << 8));
			vmeDev->write(
					BASE_ADDRESS
							+ CONTROL_BLOCK_POINTER_WRITE*2 +
								LS_RT_BASE_ADDRESS_WORD_OFFSET,
					LS_RT_CONTROL_BLOCK.BASE_ADDRESS);
			// RT LS Subaddres Descriptor Block 26
			//subaddress control word (sub addr 26)
			vmeDev->write(
					BASE_ADDRESS + (LS_RT_CONTROL_BLOCK.BASE_ADDRESS * 2)
							+ (sub_addr * 8) + SA_CONTROL_WORD_OFFSET,
					SUBADDRESS_CONTROL_WORD_UNION.raw[LOW]
							+ (SUBADDRESS_CONTROL_WORD_UNION.raw[HIGH] << 8));
			//intrface data pointer (sub addr 26)
			vmeDev->write(
					BASE_ADDRESS + (LS_RT_CONTROL_BLOCK.BASE_ADDRESS * 2)
							+ (sub_addr  * 8) + SA_INTERFACE_DATA_PNTR_OFFSET,
					SUBADDRESS_DESCRIPTOR.ITF_DATA_PTR);
			//host data pointer(sub addr 26)
			vmeDev->write(
					BASE_ADDRESS + (LS_RT_CONTROL_BLOCK.BASE_ADDRESS * 2)
							+ (sub_addr  * 8) + SA_HOST_DATA_PNTR_OFFSET,
					SUBADDRESS_DESCRIPTOR.HOST_DATA_PTR);

			vmeDev->write(
					BASE_ADDRESS + (LS_RT_CONTROL_BLOCK.BASE_ADDRESS * 2)
							+ ((sub_addr + 32)* 8) + SA_CONTROL_WORD_OFFSET,
					SUBADDRESS_CONTROL_WORD_UNION.raw[LOW]
							+ (SUBADDRESS_CONTROL_WORD_UNION.raw[HIGH] << 8));
			//intrface data pointer (sub addr 26)
			vmeDev->write(
					BASE_ADDRESS + (LS_RT_CONTROL_BLOCK.BASE_ADDRESS * 2)
							+ ((sub_addr + 32)  * 8) + SA_INTERFACE_DATA_PNTR_OFFSET,
					SUBADDRESS_DESCRIPTOR.ITF_DATA_PTR);
			//host data pointer(sub addr 26)
			vmeDev->write(
					BASE_ADDRESS + (LS_RT_CONTROL_BLOCK.BASE_ADDRESS * 2)
							+ ((sub_addr + 32)  * 8) + SA_HOST_DATA_PNTR_OFFSET,
					SUBADDRESS_DESCRIPTOR.HOST_DATA_PTR);

			vmeDev->write(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + 0x4,
								0xB0);


			vmeDev->write(BASE_ADDRESS + EFFECTIVE_DATA_ADDRESS_OFFSET,
						HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS);
			vmeDev->write(BASE_ADDRESS + TABLE_POINTER_ADDRESS_OFFSET,
						HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS);
			vmeDev->write(BASE_ADDRESS + PRSIZE_WORD_OFFSET,
						HS_CONTROL_BLOCK.PREAMBLE_S_B_WORD);
			vmeDev->write(BASE_ADDRESS + START_END_DELIMITER_FORMAT_OFFSET,
						HS_CONTROL_BLOCK.S_E_DELIMITER_FORMAT);
			/*vmeDev->write(BASE_ADDRESS + BITE_DATA_ADDRESS_OFFSET,
						HS_CONTROL_BLOCK.BITE_DATA_ADDRESS);
			vmeDev->write(BASE_ADDRESS + HS_CONTROL_BLOCK.EFFECTIVE_DATA_ADDRESS * 2,
						HS_MID_CW_DT_UNION.raw[LOW]);*/

			vmeDev->write(BASE_ADDRESS + HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS*2 + 0x4,
					HS_DATA_POINTER.ITF_DATA_PTR);
			vmeDev->write(BASE_ADDRESS + HS_CONTROL_BLOCK.TABLE_POINTER_ADDRESS*2 +0x4 + HS_IF_HOST_DATA_PNTR_OFFSET,
					HS_DATA_POINTER.HOST_DATA_PTR);


			//High Speed Data Buffer
			vmeDev->write(BASE_ADDRESS + HS_DATA_POINTER.ITF_DATA_PTR*2,
					HS_MID_CW_DT_UNION.raw[LOW]
							+ (HS_MID_CW_DT_UNION.raw[HIGH]));
			//Restart LS
			vmeDev->write(
					GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
					RESTART_LS_WRITE);

			usleep(MSEC_TO_USEC(5));

			vmeDev->read(BASE_ADDRESS + (CONTROL_BLOCK_POINTER_WRITE*2) + INTERFACE_STATUS_WORD_OFFSET,
					INTERFACE_STATUS_WORD_READ);

			if (INTERFACE_STATUS_WORD_READ != 0x0000) {
				snprintf(this->strError, MAX_BUF_SIZE,
						"Error during External Loopback Channel %c activated by LS:\n"
								"The expected value for the Interface Status Word is 0x0880,"
								"while the read value is 0x%04x", CH - 32,
						INTERFACE_STATUS_WORD_READ);
				Logger::getLogger()->Log(DEBUG_LEVEL,
						"***Error: INTERFACE STATUS WORD: the value expected was 0880, the value read is %x***",
						INTERFACE_STATUS_WORD_READ);
				return ERR_LOOP_LS_INT_STATUS_WORD;
			}
			Logger::getLogger()->Log(INFO_LEVEL,
					"***End Loopback Esterno Attivato da LS step 1***");

			return NEXT_STEP;
		} else if (step == 2) {
			Logger::getLogger()->Log(INFO_LEVEL,
					"***Start Loopback Esterno Attivato da LS step 2***");
			if (CH == 'a') {
				vmeDev->read(BASE_ADDRESS + LAST_ACTION_WORD_OFFSET,
						HS_LAST_ACTION_WORD_READ);
				if (HS_LAST_ACTION_WORD_READ != 0x4081) {
				//if (HS_LAST_ACTION_WORD_READ != 0x0000) {
					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during External Loopback Channel %c activated by LS:\n"
									"The expected value for the HS Last Action Word is 0x4080,"
									"while the read value is 0x%04x", CH - 32,
							HS_LAST_ACTION_WORD_READ);
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: HS LAST ACTION WORD: the value expected was 4080, the value read is %x***",
							HS_LAST_ACTION_WORD_READ);
					return ERR_LOOP_LS_LAST_ACT_WORD;
				}
				vmeDev->read(BASE_ADDRESS + ACTION_WORD_OFFSET,
						HS_ACTION_WORD_READ);
				    if (HS_ACTION_WORD_READ != 0x4081) {
					//if (HS_ACTION_WORD_READ != 0x0000) {
					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during External Loopback Channel %c activated by LS:\n"
									"The expected value for the HS Action Word is 0x4081,"
									"while the read value is 0x%04x", CH - 32,
							HS_ACTION_WORD_READ);
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: HS ACTION WORD: the value expected was 4081, the value read is %x***",
							HS_ACTION_WORD_READ);
					return ERR_LOOP_LS_ACTION_WORD;
				}
			} else if (CH == 'b') {
				vmeDev->read(BASE_ADDRESS + LAST_ACTION_WORD_OFFSET,
						HS_LAST_ACTION_WORD_READ);
				if (HS_LAST_ACTION_WORD_READ != 0xC081) {
				//if (HS_LAST_ACTION_WORD_READ != 0x0000) {
					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during External Loopback Channel %c activated by LS:\n"
									"The expected value for the HS Last Action Word is 0xC081,"
									"while the read value is 0x%04x", CH - 32,
							HS_LAST_ACTION_WORD_READ);
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: HS LAST ACTION WORD: the value expected was C080, the value read is %x***",
							HS_LAST_ACTION_WORD_READ);
					return ERR_LOOP_LS_LAST_ACT_WORD;
				}
				vmeDev->read(BASE_ADDRESS + ACTION_WORD_OFFSET,
						HS_ACTION_WORD_READ);
				if (HS_ACTION_WORD_READ != 0xC081) {
				//if (HS_ACTION_WORD_READ != 0x0000) {
					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during External Loopback Channel %c activated by LS:\n"
									"The expected value for the HS Action Word is 0xC081,"
									"while the read value is 0x%04x", CH - 32,
							HS_ACTION_WORD_READ);
					Logger::getLogger()->Log(INFO_LEVEL,
							"***Error: HS ACTION WORD: the value expected was C080, the value read is %x***",
							HS_ACTION_WORD_READ);
					return ERR_LOOP_LS_ACTION_WORD;
				}
			}

			Logger::getLogger()->Log(INFO_LEVEL,
					"***End Loopback Esterno Attivato da LS step 2***");
		}
	} catch (std::string &error) {
		snprintf(this->strError, MAX_BUF_SIZE, "External Loopback Channel %c activated by LS:\n"
				"Unexpected exception: %s", CH - 32,error.c_str());
		return TEST_NOK;
	}

	Logger::getLogger()->Log(INFO_LEVEL,
			"***End Loopback Esterno Attivato da LS***");

	return TEST_OK;
}

