/*
 * InterruptLSTest.cpp
 *
 *  Created on: 29/nov/2012
 *      Author: galileo
 */

#include "InterruptLSTest.h"

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Inizializzazione_LS.h"
#include "Selftest.h"
#include "Iniz_Tavola_Descr_SA_01_RX.h"
#include "Iniz_Tavola_Descr_SA_01_TX.h"
#include "I_TEST.h"

Interrupt_LS_Test::Interrupt_LS_Test() {
	// TODO Auto-generated constructor stub

}

Interrupt_LS_Test::~Interrupt_LS_Test() {
	// TODO Auto-generated destructor stub
}


UINT8 Interrupt_LS_Test::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	const UINT32 CONTROL_BLOCK_POINTER_WRITE = 0x00A8;
	Logger::getLogger()->Log(INFO_LEVEL, "***Start Interrupt Test***");

	UINT32 BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	va_list argP;
	va_start(argP, num_argomenti);
	int step = va_arg(argP, int);
	va_end(argP);

	I_TEST *iTest;
	int res;




	if(step == 1){
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
		res = iTest->execTest(bt,1,1);
		delete iTest;

		iTest = new Iniz_Tavola_Descr_SA_01_TX();
		iTest->setDevice(vmeDev);
		res = iTest->execTest(bt,1,1);
		delete iTest;
		if(res == TEST_OK)
			return NEXT_STEP;
		else
			return TEST_NOK;
	}
	else if (step == 2){
		UINT32 command_word;
		vmeDev->read(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 + LS_RT_COMMAND_WORD_LIST_POINTER,command_word);
		//vmeDev->read(BASE_ADDRESS + 0x200,command_word);
		if((command_word-0x300) != 0x10){
			snprintf(this->strError,MAX_BUF_SIZE,"Error during Interrupt Test:\n"
					"The expected value for the Command Word List Pointer is 0x10,"
					"while the read value is 0x%04x", command_word);

			Logger::getLogger()->Log(INFO_LEVEL,
					"***Error: Interrupt Test: the value expected was 0x8, the value read is %x***",
					command_word);
			return TEST_NOK;
		}
	}


	return TEST_OK;
}

