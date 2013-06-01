/*
 * IF_Optimized_Bus_Test.cpp
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include "IF_Optimized_Bus_Test.h"
#include <stdio.h>
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

enum EN_ERROR_HS_SELFTEST {
	ERR_OPT_BUS_ONE_WALK = TEST_CUSTOM_ERR,
	ERR_OPT_BUS_ADDR_ONE_WALK,
	ERR_OPT_BUS_PATTERN,
	ERR_OPT_BUS_PATTERN_DOUBLE,
	ERR_OPT_BUS_PATTERN_BYTE,
	ERR_OPT_BUS_PATTERN_WORD,
	ERR_OPT_BUS_PATTERN_THREE
};

IF_Optimized_Bus_Test::IF_Optimized_Bus_Test() {
	uno_walking = 0x1;
	pattern_double_word[0] = 0xCCCC3333;
	pattern_double_word[1] = 0x3333CCCC;
	pattern_double_word[2] = 0xCC33CC33;
	pattern_double_word[3] = 0x33CC33CC;
	pattern_double_word[4] = 0xC3C3C3C3;
	pattern_double_word[5] = 0x3C3C3C3C;
	pattern_double_word[6] = 0xAAAA5555;
	pattern_double_word[7] = 0x5555AAAA;
	pattern_double_word[8] = 0xAA55AA55;
	pattern_double_word[9] = 0x55AA55AA;
	pattern_double_word[10] = 0xA5A5A5A5;
	pattern_double_word[11] = 0x5A5A5A5A;
        // PATTERN NUOVI
        pattern_double_word[12] = 0xFFFF0000;
        pattern_double_word[13] = 0x0000FFFF;
        pattern_double_word[14] = 0xFF00FF00;
        pattern_double_word[15] = 0x00FF00FF;
        pattern_double_word[16] = 0xF0F0F0F0;
        pattern_double_word[15] = 0x0F0F0F0F;

	pattern_byte[0] = 0xFF;
	pattern_byte[1] = 0xAA;
	pattern_byte[2] = 0x11;
	pattern_byte[3] = 0x00;
	pattern_word[0] = 0xFFFF;
	pattern_word[1] = 0x0000;
	pattern_word[2] = 0x5555;
	pattern_word[3] = 0xAAAA;
	pattern_three_byte[0] = 0x00FFFF;
	pattern_three_byte[1] = 0x555500;
	pattern_three_byte[2] = 0x0FAAAA;
	pattern_three_byte[3] = 0xF0F00F;
}

UINT8 IF_Optimized_Bus_Test::execTest(const BoardInterfaceType& bt,
		int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start IF Optimized Bus Test***");

	RT_Reg regAddress;
	regAddress.reg.RTA_A0_W = 1;
	regAddress.reg.RTA_A_SEL_W = 1;

	/*	va_list argP;
	 va_start(argP, num_argomenti);
	 va_end(argP);
	 */
	bool isSimpBoard = (strcmp(GlobalData::instance()->GetInterfaceData(bt)->board_name,"SIMP1") == 0) ||
			           (strcmp(GlobalData::instance()->GetInterfaceData(bt)->board_name,"SIMP2") == 0);
	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;


	/*! Validazione del Bus Dati
	 *
	 */
	uno_walking = 1;
	for (int k = 0; k < 32; ++k) {
		//vmeDev->write(BASE_ADDRESS, uno_walking << k, EN_VME_DOUBLE_WORD);
		//vmeDev->read(BASE_ADDRESS, uno_walking_read, EN_VME_DOUBLE_WORD);
		vmeDev->write(BASE_ADDRESS, uno_walking << k);
		vmeDev->read(BASE_ADDRESS, uno_walking_read);
		if ((uno_walking_read & 0xFFFF)!= ((uno_walking << k) & 0xFFFF)) {
			//vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error: IF Optimized Bus Test: the value expected in the uno walking was %x, the value read is %x***",
					uno_walking << k, uno_walking_read);
			snprintf(this->strError, MAX_BUF_SIZE,
					"Error during I/F Optimized Bus Test:\n"
							"Expected value during one-walking data bus at address 0x%04x"
							" is 0x%04x, while read value is 0x%04x.",BASE_ADDRESS,
					(uno_walking << k), uno_walking_read);

			return ERR_OPT_BUS_ADDR_ONE_WALK;

		}
	}

	usleep(MSEC_TO_USEC(100));

	/*! Validazione del Bus Indirizzi
	 *
	 */

	/*	int shift = 0; */
	UINT32 data = 1;
	UINT8 data_write = 1;
	try {
		for (UINT32 offset = 0;	offset < (GlobalData::instance()->GetInterfaceData(bt)->memory_size);) {
			if(isSimpBoard){
				vmeDev->write(BASE_ADDRESS + offset, data_write);
				vmeDev->read(BASE_ADDRESS + offset, data);
				if(data != data_write){
					vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
					Logger::getLogger()->Log(DEBUG_LEVEL,
											"***Error: IF Optimized Bus Test: the value expected in the uno walking was %x, the value read is %x***",
											data_write, data);
					snprintf(this->strError, MAX_BUF_SIZE,
											"Error during I/F Optimized Bus Test:\n"
													"Expected value during one-walking test at address 0x%04x"
													"is 0x%04x, while read value is 0x%04x.",
													BASE_ADDRESS + offset, data_write, data);

					return ERR_OPT_BUS_ONE_WALK;
				}
			}
			else
				vmeDev->write(BASE_ADDRESS + offset, data_write, EN_VME_BYTE);
			++data_write;
			if(offset == 0)
				offset=2;
			else
				offset <<= 1;
		}

		/*	shift = 0; */
		UINT8 data_write = 1;
		for (UINT32 offset = 0;	offset < (GlobalData::instance()->GetInterfaceData(bt)->memory_size);) {
			if(isSimpBoard)
				vmeDev->read(BASE_ADDRESS + offset, data);
			else
				vmeDev->read(BASE_ADDRESS + offset, data, EN_VME_BYTE);
			if (data != data_write) {
				vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
				Logger::getLogger()->Log(DEBUG_LEVEL,
						"***Error: IF Optimized Bus Test: the value expected in the uno walking was %x, the value read is %x***",
						data_write, data);
				snprintf(this->strError, MAX_BUF_SIZE,
						"Error during I/F Optimized Bus Test:\n"
								"Expected value during one-walking test at address 0x%04x"
								"is 0x%04x, while read value is 0x%04x.",
								BASE_ADDRESS + offset, data_write, data);

				return ERR_OPT_BUS_ONE_WALK;
			}
			if(offset == 0)
				offset=2;
			else
				offset <<= 1;
			++data_write;
		}

		usleep(MSEC_TO_USEC(100));


		if(!isSimpBoard){
			for (int k = 0; k < 12; ++k) {
				vmeDev->write(BASE_ADDRESS + 0x4, pattern_double_word[k],
						EN_VME_DOUBLE_WORD);
				usleep(500);
				vmeDev->read(BASE_ADDRESS + 0x4, pattern_double_word_read,
						EN_VME_DOUBLE_WORD);
				if (pattern_double_word_read != pattern_double_word[k]) {
					vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: IF Optimized Bus Test: the value expected was %x, the value read is %x***",
							pattern_double_word[k], pattern_double_word_read);
					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during I/F Optimized Bus Test:\n"
							"Expected value during pattern double word access test at address 0x%04x is 0x%04x, while read value is 0x%04x.",
							BASE_ADDRESS + 0x4, pattern_double_word[k], pattern_double_word_read);
					return ERR_OPT_BUS_PATTERN;
				}
			}
		}

		/*! Validazione del tipo di accesso
		 *
		 */
		if(!isSimpBoard){
			for (int k = 0; k < 4; ++k) {
				vmeDev->write(BASE_ADDRESS + 0x8, pattern_byte[k], EN_VME_BYTE);
				usleep(500);
				vmeDev->read(BASE_ADDRESS + 0x8, pattern_byte_read, EN_VME_BYTE);
				if (pattern_byte_read != pattern_byte[k]) {
					vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: IF Optimized Bus Test: the value expected was %x, the value read is %x***",
							pattern_byte[k], pattern_byte_read);
					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during I/F Optimized Bus Test:\n"
							"Expected value during pattern byte access test at address 0x%04x is 0x%04x, while read value is 0x%04x.",
							BASE_ADDRESS + 0x8, pattern_byte[k], pattern_byte_read);

					return ERR_OPT_BUS_PATTERN_BYTE;
				}
			}
		}

		usleep(MSEC_TO_USEC(100));

		for (int k = 0; k < 4; ++k) {
			vmeDev->write(BASE_ADDRESS + 0xC, pattern_word[k], EN_VME_WORD);
			usleep(500);
			vmeDev->read(BASE_ADDRESS + 0xC, pattern_word_read, EN_VME_WORD);
			if (pattern_word_read != pattern_word[k]) {
				vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
				Logger::getLogger()->Log(DEBUG_LEVEL,
						"***Error: IF Optimized Bus Test: the value expected was %x, the value read is %x***",
						pattern_word[k], pattern_word_read);
				snprintf(this->strError, MAX_BUF_SIZE,
						"Error during I/F Optimized Bus Test:\n"
						"Expected value during pattern word access test at address 0x%04x is 0x%04x, while read value is 0x%04x.",
						BASE_ADDRESS + 0x8, pattern_word[k], pattern_word_read);
				return ERR_OPT_BUS_PATTERN_WORD;
			}
		}

		if(!isSimpBoard){
			for (int k = 0; k < 4; ++k) {
				vmeDev->write(BASE_ADDRESS + 0x10, pattern_three_byte[k],
						EN_VME_TRIPLE_BYTE);
				vmeDev->read(BASE_ADDRESS + 0x10, pattern_three_byte_read,
						EN_VME_TRIPLE_BYTE);
				if (pattern_three_byte_read != pattern_three_byte[k]) {
					vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: IF Optimized Bus Test: the value expected was %x, the value read is %x***",
							pattern_three_byte[k], pattern_three_byte_read);
					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during I/F Optimized Bus Test:\n"
							"Expected value during pattern word access test at address 0x%04x is 0x%04x, while read value is 0x%04x.",
							BASE_ADDRESS + 0x10, pattern_three_byte[k], pattern_three_byte_read);
					return ERR_OPT_BUS_PATTERN_THREE;

				}
			}
		}

		if(!isSimpBoard){
			for (int k = 0; k < 4; ++k) {
				vmeDev->write(BASE_ADDRESS + 0x14, pattern_double_word[k],
						EN_VME_DOUBLE_WORD);
				vmeDev->read(BASE_ADDRESS + 0x14, pattern_double_word_read,
						EN_VME_DOUBLE_WORD);
				if (pattern_double_word_read != pattern_double_word[k]) {
					vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal), regAddress.raw32);
					Logger::getLogger()->Log(DEBUG_LEVEL,
							"***Error: IF Optimized Bus Test: the value expected was %x, the value read is %x***",
							pattern_double_word[k], pattern_double_word_read);
					snprintf(this->strError, MAX_BUF_SIZE,
							"Error during I/F Optimized Bus Test:\n"
							"Expected value during pattern word access test at address 0x%04x is 0x%04x, while read value is 0x%04x.",
							BASE_ADDRESS + 0x14, pattern_double_word[k], pattern_double_word_read);

					return ERR_OPT_BUS_PATTERN_DOUBLE;
				}
			}
		}
	} catch (std::string &error) {
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during Optimized Bus Test:\n"
						"Fatal error during access on VME bus address: %s",
				error.c_str());
		return TEST_NOK;
	}

	Logger::getLogger()->Log(DEBUG_LEVEL,
			"***End IF Optimized Bus Test. Status passed.***");

	return TEST_OK;
}

