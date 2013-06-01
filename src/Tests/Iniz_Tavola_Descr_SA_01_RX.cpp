/*
 * Iniz_Tavola_Descr_SA_01_RX.cpp
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include "Iniz_Tavola_Descr_SA_01_RX.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"

Iniz_Tavola_Descr_SA_01_RX::Iniz_Tavola_Descr_SA_01_RX() {
	SUBADDRESS_DESCRIPTOR.ITF_DATA_PTR = 0x0780;
	SUBADDRESS_DESCRIPTOR.HOST_DATA_PTR = 0x0780;
	SUBADDRESS_DESCRIPTOR.TIME_TAG_WORD = 0x0;
	LS_RT_CONTROL_BLOCK.BASE_ADDRESS = 0x00B4;
}

UINT8 Iniz_Tavola_Descr_SA_01_RX::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Iniz Tavola Descr SA 01 RX***");
	UINT16 subaddress_ctrl_word = 0x0;
	va_list argP;
	va_start(argP, num_argomenti);
	RCI = va_arg(argP, int);
	va_end(argP);

	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;

	if(RCI == 1) {
		/*SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.WORD_COUNT = 0x0;
		SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.ZERO = 0x0;
		SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.RCN = 0x0;
		SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.MDI = 0x0;
		SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.SIL = 0x0;
		SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.EDB = 0x0;
		SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.ERI = 0x0;
		SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.RCI = 0x1;
		SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.MRE = 0x0;*/
		subaddress_ctrl_word = 0x4000; //RCI bit = 1
	} else {
		/*SUBADDRESS_CONTROL_WORD_UNION.raw[LOW] = 0x0;
		SUBADDRESS_CONTROL_WORD_UNION.raw[HIGH] = 0x0;*/
		subaddress_ctrl_word = 0x0; //RCI bit = 0
	}
	vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 0x8,subaddress_ctrl_word);
	/*if(RCI == 0) {
		vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 0x8,
				SUBADDRESS_CONTROL_WORD_UNION.raw[LOW] + (SUBADDRESS_CONTROL_WORD_UNION.raw[HIGH] << 8));
	} else if(RCI == 1) {
		vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 0x8,
				SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.WORD_COUNT);
		vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 0x8,
				SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.ZERO);
		vmeDev->write(BASE_ADDRESS + LS_RT_DESC_TABLE_RX_OFFSET + 0x8,
				SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.RCN);
		vmeDev->write(BASE_ADDRESS + LS_RT_DESC_TABLE_RX_OFFSET + 0x8,
				SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.MDI);
		vmeDev->write(BASE_ADDRESS + LS_RT_DESC_TABLE_RX_OFFSET + 0x8,
				SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.SIL);
		vmeDev->write(BASE_ADDRESS + LS_RT_DESC_TABLE_RX_OFFSET + 0x8,
				SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.EDB);
		vmeDev->write(BASE_ADDRESS + LS_RT_DESC_TABLE_RX_OFFSET + 0x8,
				SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.ERI);
		vmeDev->write(BASE_ADDRESS + LS_RT_DESC_TABLE_RX_OFFSET + 0x8,
				SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.RCI);
		vmeDev->write(BASE_ADDRESS + LS_RT_DESC_TABLE_RX_OFFSET + 0x8,
				SUBADDRESS_DESCRIPTOR.SUBADDRESS_CONTROL.MRE);
	}*/

	vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 0xA,
			SUBADDRESS_DESCRIPTOR.ITF_DATA_PTR);
	vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 0xC,
			SUBADDRESS_DESCRIPTOR.HOST_DATA_PTR);
	vmeDev->write(BASE_ADDRESS + LS_RT_CONTROL_BLOCK.BASE_ADDRESS*2 + 0xE,
			SUBADDRESS_DESCRIPTOR.TIME_TAG_WORD);

	Logger::getLogger()->Log(INFO_LEVEL, "***End Iniz Tavola Descr SA 01 RX***");

	return TEST_OK;
}



