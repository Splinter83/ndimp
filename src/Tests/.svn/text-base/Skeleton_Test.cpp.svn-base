/*
 * Skeleton_Test.cpp
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Skeleton_Test.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Inizializzazione_LS.h"
#include "Selftest.h"
#include "Iniz_Tavola_Descr_SA_01_RX.h"
#include "Iniz_Tavola_Descr_SA_01_TX.h"
#include "I_TEST.h"

Skeleton_Test::Skeleton_Test() {
	pattern_word[0] = 0xFFFF;
	pattern_word[1] = 0x0000;
	pattern_word[2] = 0x5555;
	pattern_word[3] = 0xAAAA;
	pattern_word[4] = 0x0F0F;
	pattern_word[5] = 0xF0F0;
	pattern_word[6] = 0x0000;
}

UINT8 Skeleton_Test::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Skeleton Test***");

	va_list argP;
	va_start(argP, num_argomenti);
	int step = va_arg(argP, int);
	va_end(argP);

	I_TEST *iTest;
	int res;

	iTest = new Selftest();
	iTest->setDevice(vmeDev);
	res = iTest->execTest(bt);
	delete iTest;
	iTest = new Inizializzazione_LS();
	iTest->setDevice(vmeDev);
	res = iTest->execTest(bt);
	delete iTest;
	iTest = new Iniz_Tavola_Descr_SA_01_RX();
	iTest->setDevice(vmeDev);
	res = iTest->execTest(bt,1,0);
	delete iTest;

	iTest = new Iniz_Tavola_Descr_SA_01_TX();
	iTest->setDevice(vmeDev);
	res = iTest->execTest(bt,1,0);
	delete iTest;

	SKELETON_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->arbitered_io + 0x4;
	try{
	//int count = 0;
		switch(step){
			case 1: //TFF Bit
				vmeDev->write(SKELETON_ADDRESS,0x1);
				return NEXT_STEP;
			break;
			case 2:
				vmeDev->write(SKELETON_ADDRESS,0x2);
				return NEXT_STEP;
			break;
			case 3:
				vmeDev->write(SKELETON_ADDRESS,0x4);
				return NEXT_STEP;
			break;
			case 4:
				vmeDev->write(SKELETON_ADDRESS,0x8);
				return NEXT_STEP;
			break;
			case 5:
				vmeDev->write(SKELETON_ADDRESS,0x100);
			break;
		}
	}catch(std::string &error)
	{
		if(step <= 4){
			snprintf(this->strError,MAX_BUF_SIZE,"Error during Skeleton Bus Test:\n"
				"Write error at bit %d ", step);
		}
		else{
			snprintf(this->strError,MAX_BUF_SIZE,"Error during Skeleton Bus Test:\n"
				"Write error at bit 8");
		}
	}



	Logger::getLogger()->Log(INFO_LEVEL, "***End Skeleton Test***");

	return TEST_OK;
}

