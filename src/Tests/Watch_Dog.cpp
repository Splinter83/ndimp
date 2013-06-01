/*
 * Watch_Dog.cpp
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include "Watch_Dog.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "global_definitions.h"
#include "Singleton.h"
#include "ConfigFile.h"

Watch_Dog::Watch_Dog(){
	RESTART_LS_WRITE = 0x0001;
	iniz_LS = Inizializzazione_LS();
	iniz_descr_RX = Iniz_Tavola_Descr_SA_01_RX();
	iniz_descr_TX = Iniz_Tavola_Descr_SA_01_TX();
}

Watch_Dog::~Watch_Dog() {
}

UINT8 Watch_Dog::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Watch Dog***");
	I_TEST *iTest;
	UINT32 res = TEST_NOK;
	va_list argP;
	va_start(argP, num_argomenti);
	int step = va_arg(argP, int);
	UINT32 term = va_arg(argP, UINT32);
	va_end(argP);

	GeneralConfigReg generalConf;

	//Disable ENWDEX
	vmeDev->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal), generalConf.raw32);

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	if (step == 1) {
		Logger::getLogger()->Log(INFO_LEVEL, "***Start Watch Dog step 1***");

		generalConf.reg.ENWDEXT = 0;
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),generalConf.raw32);
		//Reset (MCL)
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear

		iTest = new Inizializzazione_LS();
		iTest->setDevice(vmeDev);
		res = iTest->execTest(bt);
		delete iTest;
		if(res != TEST_OK){
			strcpy(this->strError,iTest->getError());
			return res*100;
		}
		iTest = new Iniz_Tavola_Descr_SA_01_RX();
		iTest->setDevice(vmeDev);
		res = iTest->execTest(bt,1,0);
		delete iTest;
		if(res != TEST_OK){
			strcpy(this->strError,iTest->getError());
			return res*1000;
		}
		iTest = new Iniz_Tavola_Descr_SA_01_TX();
		iTest->setDevice(vmeDev);
		res = iTest->execTest(bt,1,0);
		delete iTest;
		if(res != TEST_OK){
			strcpy(this->strError,iTest->getError());
			return res*10000;
		}
		//Restart
		vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
				1);

		Logger::getLogger()->Log(INFO_LEVEL, "***End Watch Dog step 1***");
		return NEXT_STEP;
	} else if (step == 2) {
		Logger::getLogger()->Log(INFO_LEVEL, "***Start Watch Dog step 2***");
		vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io, RESTART_LS_WRITE);
		usleep(MSEC_TO_USEC(5));
		vmeDev->read(BASE_ADDRESS + LS_RT_INTERFACE_CONTROL_WORD_OFFSET,
				INTERFACE_CONTROL_WORD_READ);
		rt_add = INTERFACE_CONTROL_WORD_READ & RT_ICW_TA;
		if (rt_add != term) {
			Logger::getLogger()->Log(INFO_LEVEL,
					"***Error: RT_ADDRESS: the value expected was %x, the value read is %x***",
					term, rt_add);
		}
		Logger::getLogger()->Log(INFO_LEVEL, "***End Watch Dog step 2***");
		return NEXT_STEP;
	} else if (step == 3) {
		Logger::getLogger()->Log(INFO_LEVEL, "***Start Watch Dog step 3***");
		//Disable WatchDog
		generalConf.reg.ENWDEXT = 0;
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),generalConf.raw32);
		//Reset (MCL)
		vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
		Logger::getLogger()->Log(INFO_LEVEL, "***End Watch Dog step 3***");
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End Watch Dog***");

	return 0;
}

