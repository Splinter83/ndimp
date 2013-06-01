/*
 * Watch_Dog_Test.cpp
 *
 *  Created on: 10/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Watch_Dog_Test.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Inizializzazione_LS.h"
#include "Selftest.h"
#include "Iniz_Tavola_Descr_SA_01_RX.h"
#include "Iniz_Tavola_Descr_SA_01_TX.h"
#include "Singleton.h"
#include "ConfigFile.h"

Watch_Dog_Test::Watch_Dog_Test() {

}

UINT8 Watch_Dog_Test::execTest(const BoardInterfaceType& bt, int num_argomenti,
		...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Watch Dog Test***");

	va_list argP;
	va_start(argP, num_argomenti);
	int step = va_arg(argP, int);
	va_end(argP);
	GeneralConfigReg generalConf;
	UINT32 currentConfig;
	I_TEST *iTest = NULL;
	//Will be reset with previous configuration before return from test
	vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal), currentConfig);

	vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal), generalConf.raw32);

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	if (step == 1) {
		int res = 0;
		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***Start Watch Dog Test step 1***");

		//Set ENWDEXT to 1
		generalConf.reg.ENWDEXT = 1;
		if(bt == STIMP_ATTACK_3910 || bt == STIMP_AVIONIC_3910)
			generalConf.reg.ENWDLS = 1;
		else
			generalConf.reg.ENWDLS = 0;
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal), generalConf.raw32);
		//Reset (MCL)
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal), 0); // Master Clear
		usleep(SEC_TO_USEC(2));
		iTest = new Selftest();
		iTest->setDevice(vmeDev);
		res = iTest->execTest(bt);
		if(res != TEST_OK){
			strcpy(this->strError,iTest->getError());
			delete iTest;			
			return res*10;
		}
		delete iTest;
		iTest = new Inizializzazione_LS();
		iTest->setDevice(vmeDev);
		res = iTest->execTest(bt);
		if(res != TEST_OK){
			strcpy(this->strError,iTest->getError());
			delete iTest;			
			return res*100;
		}
		delete iTest;
		iTest = new Iniz_Tavola_Descr_SA_01_RX();
		iTest->setDevice(vmeDev);
		res = iTest->execTest(bt, 1, 0);
		if(res != TEST_OK){
			strcpy(this->strError,iTest->getError());
			delete iTest;			
			return res*1000;
		}
		delete iTest;

		iTest = new Iniz_Tavola_Descr_SA_01_TX();
		iTest->setDevice(vmeDev);
		res = iTest->execTest(bt, 1, 0);
		if(res != TEST_OK){
			strcpy(this->strError,iTest->getError());
			delete iTest;			
			return res*10000;
		}
		delete iTest;

		return NEXT_STEP;
	}
	if (step == 2) {
		UINT32 CONTROL_BLOCK_POINTER = 0x00A8;
		UINT32 data_read;
		vmeDev->read(
				BASE_ADDRESS
						+ CONTROL_BLOCK_POINTER
								* 2+ INTERFACE_STATUS_WORD_OFFSET, data_read);

		UINT16 tmp = (data_read & 0x208);

		if (tmp == 0) {
			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error read Interface Status Word, LWT 0x%04x***",
					data_read);
			snprintf(this->strError, MAX_BUF_SIZE, "Error during Watchdog:\n"
					"Error read Interface Status Word, LWT 0x%04x", data_read);
			delete iTest;
			return TEST_NOK;
		}

		vmeDev->read(
				BASE_ADDRESS
						+ CONTROL_BLOCK_POINTER
								* 2+ LS_RT_ERROR_BITE_WORD_OFFSET, data_read);
		if ((data_read & 0x10) == 0) {
			Logger::getLogger()->Log(DEBUG_LEVEL,
					"***Error read Error Bite Word, EBW 0x%04x***", data_read);
			snprintf(this->strError, MAX_BUF_SIZE, "Error during Watchdog:\n"
					"Error read Error BITE word, EBW 0x%04x", data_read);
			delete iTest;
			return TEST_NOK;
		}

		delete iTest;
		return TEST_OK;

		Logger::getLogger()->Log(DEBUG_LEVEL,
				"***End Watch Dog Test step 8***");
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End Watch Dog Test***");

	//Reset
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal), currentConfig);

	return TEST_OK;
}

