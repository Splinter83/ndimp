/*
 * Iniz_Tavola_Descr_SA_01_TX.cpp
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Iniz_Tavola_Descr_SA_01_TX.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"

#define RTA_MASK 0x07C00000
#define RTB_MASK 0x001F0000

Iniz_Tavola_Descr_SA_01_TX::Iniz_Tavola_Descr_SA_01_TX() {
	SUBADDRESS_DESCRIPTOR.ITF_DATA_PTR = 0x780;
	SUBADDRESS_DESCRIPTOR.HOST_DATA_PTR = 0x780;
	SUBADDRESS_DESCRIPTOR.TIME_TAG_WORD = 0x0;
	LS_RT_CONTROL_BLOCK.BASE_ADDRESS = 0x00B4;
	RESTART_LS_WRITE = 0x0001;
	CONTROL_BLOCK_POINTER_WRITE = 0x00A8;
}

UINT8 Iniz_Tavola_Descr_SA_01_TX::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Iniz Tavola Descr SA 01 TX***");

	UINT16 subaddress_ctrl_word = 0x0;
	UINT8 term = 0;

	va_list argP;
	va_start(argP, num_argomenti);
	RCI = va_arg(argP, int);
	va_end(argP);

	term = GlobalData::instance()->GetRemoteTerminalAddr((RemoteTerminalSide)GlobalData::instance()->GetInterfaceData(bt)->side);

	if(bt == SIMP1_BSD_EDDL || bt == SIMP1_CSMU_EDDL || /*bt == SIMP1_MDP_EDDL ||*/
	   bt == SIMP2_EMU1_EDDL || bt == SIMP2_EMU2_EDDL){
		term = 0;
	}
	else if(term == 0xFF){
		RT_Reg rt_reg;
		vmeDev->readConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal),rt_reg.raw32);
		if(GlobalData::instance()->GetInterfaceData(bt)->side == RT_A)
			term = ((rt_reg.raw32 & RTA_MASK)>>22) & 0x1F;
		else
			term = ((rt_reg.raw32 & RTB_MASK)>>16) & 0x1F;
	}


	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	if(RCI == 1) {
		subaddress_ctrl_word = 0x4000; //RCI bit = 1
	} else {
		subaddress_ctrl_word = 0x0; //RCI bit = 0
	}

	vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 32*8 + 0x8,subaddress_ctrl_word);


	vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 32*8 + 0xA,
			SUBADDRESS_DESCRIPTOR.ITF_DATA_PTR);
	vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 32*8 + 0xC,
			SUBADDRESS_DESCRIPTOR.HOST_DATA_PTR);
	vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 32*8 + 0xE,
			SUBADDRESS_DESCRIPTOR.TIME_TAG_WORD);
	vmeDev->write(GlobalData::instance()->GetInterfaceData(bt)->arbitered_io,
			RESTART_LS_WRITE);

	usleep(MSEC_TO_USEC(50));

	vmeDev->read(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 +  LS_RT_INTERFACE_CONTROL_WORD_OFFSET,
			INTERFACE_CONTROL_WORD_READ);
	rt_add = INTERFACE_CONTROL_WORD_READ & RT_ICW_TA;
	rt_add >>= 11;
	if (rt_add != term) {
		snprintf(this->strError, MAX_BUF_SIZE,
				"Error during LS Selftest:\n"
				"Unexpected Remote Terminal: expected value in 0x%04x is 0x%04x, while read value is 0x%04x.",
				BASE_ADDRESS + 0x14, term, rt_add);
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: Iniz Tavola Descr SA 01 TX: the value expected of the rt address was %x, the value read is %x***",
				term, rt_add);
		return TEST_NOK;
	}

	/** TODO
	 * to be removed
	 */
	vmeDev->read(BASE_ADDRESS + CONTROL_BLOCK_POINTER_WRITE*2 +  INTERFACE_STATUS_WORD_OFFSET,
			INTERFACE_CONTROL_WORD_READ);

	Logger::getLogger()->Log(INFO_LEVEL, "***End Iniz Tavola Descr SA 01 TX***");

	return TEST_OK;
}




