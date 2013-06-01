/*
 * BitHistoryTest.cpp
 *
 *  Created on: 19/nov/2012
 *      Author: grande
 */
#define SLEEP_EPROM_TIME 35

#include "BitHistoryTest.h"
#include "Logger.h"

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#include "external_vars.h"
#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"


BitHistory_Test::BitHistory_Test() {
	// TODO Auto-generated constructor stub

}

BitHistory_Test::~BitHistory_Test() {
	// TODO Auto-generated destructor stub
}

UINT8 BitHistory_Test::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start BitHistory Test***");

/*	va_list argP;
	va_start(argP, num_argomenti);
	va_end(argP);
*/
	UINT32 BIT_HIS_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->bit_history_addr;
	UINT32 BIT_HIS_MEM_SIZE =  GlobalData::instance()->GetInterfaceData(bt)->bit_history_size;

	UINT32 data = 1;
	for (UINT32 offset = 0;	offset < BIT_HIS_MEM_SIZE;) {
		vmeDev->write(BIT_HIS_ADDRESS + offset, data & 0xFF);
		++data;


		if(offset == 0)
			offset+=2;
		else
			offset <<= 1;

		usleep(MSEC_TO_USEC(SLEEP_EPROM_TIME));
	}

	usleep(MSEC_TO_USEC(SLEEP_EPROM_TIME));

	/*	shift = 0; */
	UINT8 data_write = 1;
	for (UINT32 offset = 0;	offset < BIT_HIS_MEM_SIZE;) {
		vmeDev->read(BIT_HIS_ADDRESS + offset, data);
		if ((data &0xFF)!= (data_write & 0xFF)) {
			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: Bit History Test: the value expected in the uno walking was %x, the value read is %x***",
					data_write, data);
			snprintf(this->strError, MAX_BUF_SIZE,
					"Error during Bit History  Test:\n"
					"Expected value during one-walking test at address 0x%04x"
					"is 0x%04x, while read value is 0x%04x.",
					BIT_HIS_ADDRESS + offset, data_write, data);

			return ERR_HIS_ONE_WALK;
		}
		if(offset == 0)
			offset+=2;
		else
			offset <<= 1;

		++data_write;
	}


	for (UINT32 i = 0; i < BIT_HIS_MEM_SIZE; i+=2) {
		vmeDev->write(BIT_HIS_ADDRESS + i, (~(i) & 0xFF));
		usleep(MSEC_TO_USEC(SLEEP_EPROM_TIME));
	}

	usleep(MSEC_TO_USEC(SLEEP_EPROM_TIME));

	for (UINT32 i = 0; i < BIT_HIS_MEM_SIZE; i+=2) {
		vmeDev->read(BIT_HIS_ADDRESS +  i, word_read);
		if ((word_read & 0xFF)!= ((~ i) & 0xFF)) {
			snprintf(this->strError,MAX_BUF_SIZE,"Error during Bit History Test:\n"
					"The expected value at address 0x%08x is 0x%04x,"
					"while the read value is 0x%04x", BIT_HIS_ADDRESS +  i, ((~ i) & 0xFFFF), word_read);

			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: Bit History: the value expected at address %x was %x, the value read is %x***",
					BIT_HIS_ADDRESS + i, (~ i) & 0xFFFF,
					word_read);
			return ERR_HIS_COMPL;
		}
	}

	UINT8 toggle = 0;
	for (UINT32 i = 0; i < BIT_HIS_MEM_SIZE; i+=2) {
		if (toggle % 2 == 0) {
			vmeDev->write(BIT_HIS_ADDRESS + i, 0x00);
		} else {
			vmeDev->write(BIT_HIS_ADDRESS + i, 0xFF);
		}
		++toggle;

		usleep(MSEC_TO_USEC(SLEEP_EPROM_TIME));
	}

	usleep(MSEC_TO_USEC(SLEEP_EPROM_TIME));

	toggle = 0;
	for (UINT32 i = 0; i < BIT_HIS_MEM_SIZE; i+=2) {
		vmeDev->read(BIT_HIS_ADDRESS + i, word_read);
		if (toggle % 2 == 0) {
			if ((word_read & 0xFF)!= 0x00) {
				snprintf(this->strError,MAX_BUF_SIZE,"Error during Bit History Test:\n"
						"The expected value at address 0x%08x is 0x0000,"
						"while the read value is 0x%04x", BIT_HIS_ADDRESS +  i, word_read);
				Logger::getLogger()->Log(INFO_LEVEL,
						"***Error: Bit History Test: the value expected at address %x was %x, the value read is %x***",
						BIT_HIS_ADDRESS + i, 0x00, word_read);
				return ERR_HIS_TOGGLE;
			}
		} else {
			if ((word_read & 0xFF) != 0xFF) {
				snprintf(this->strError,MAX_BUF_SIZE,"Error during Bit History Test:\n"
						"The expected value at address 0x%08x is 0xffff,"
						"while the read value is 0x%04x", BIT_HIS_ADDRESS +  i, word_read);
				Logger::getLogger()->Log(INFO_LEVEL,
						"***Error: Bit History Test: the value expected at address %x was %x, the value read is %x***",
						BIT_HIS_ADDRESS + i, 0xFF, word_read);
				return ERR_HIS_TOGGLE;
			}
		}
		++toggle;
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End Bit History Test***");

	return TEST_OK;
}

