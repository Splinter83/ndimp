/*
 * HIACT_LODEM.cpp
 *
 *  Created on: 12/set/2012
 *      Author: grande, savino (27/11/12)
 */

#include <unistd.h>
#include <stdio.h>
#include "HIACT_LODEM.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"
#include "Singleton.h"
#include "ConfigFile.h"


HIACT_LODEM::HIACT_LODEM() {

}

UINT8 HIACT_LODEM::execTest(const BoardInterfaceType& bt, int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start HIACT_LODEM***");


	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;
	UINT32 DIRECT_IO = GlobalData::instance()->GetInterfaceData(bt)->direct_io;


	if( bt == STIMP_AVIONIC_3910)
	{
		HANDOVER_STATUS_WORD_REG  = DIRECT_IO + AVIONIC_ADDR + 0x8;
		HANDOVER_CONTROL_WORD_REG = DIRECT_IO + AVIONIC_ADDR;
		HANDOVER_MINOR_LOOP_TIMER = DIRECT_IO + AVIONIC_ADDR + 0xA;
	}
	else
	{
		HANDOVER_STATUS_WORD_REG  = DIRECT_IO + ATTACK_ADDR + 0x8;
		HANDOVER_CONTROL_WORD_REG = DIRECT_IO + ATTACK_ADDR;
		HANDOVER_MINOR_LOOP_TIMER = DIRECT_IO + ATTACK_ADDR + 0xA;
	}

	//MCL
	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0x1);
	usleep(MSEC_TO_USEC(500));

	//Timer
	vmeDev->write(HANDOVER_MINOR_LOOP_TIMER, 0xFFC3);

	//SET
	vmeDev->write(HANDOVER_CONTROL_WORD_REG, 0x3);

	//TEST
	vmeDev->read(HANDOVER_STATUS_WORD_REG, BC_STATUS_WORD_READ);

	ACT = BC_STATUS_WORD_READ & 0x1;

	if(ACT != 1) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag ACT: the value expected was 1, the value read is %x***",
				ACT);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag ACT: the value expected was 1, the value read is %x***",
				ACT);

		return ERR_ACT_HL;
	}

	DEM = (BC_STATUS_WORD_READ >> 0x1 ) & 0x1;
	if(DEM != 1) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag DEM: the value expected was 1, the value read is %x***",
				DEM);
		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag DEM: the value expected was 1, the value read is %x***",
				DEM);

		return ERR_DEM_HL;
	}

	BC_STATUS_WORD_READ = 0x0;

	//TEST
	UINT8 flag = 0;
	for(int i = 0; i < 20; i++)
	{
		vmeDev->read(HANDOVER_STATUS_WORD_REG, BC_STATUS_WORD_READ);

		if( BC_STATUS_WORD_READ == 0xe03)
		{
			flag = 1;
			break;
		}

		usleep(SEC_TO_USEC(1));

		Logger::getLogger()->Log(INFO_LEVEL,"BC_STATUS_WORD_READ is %x*** i is %d", BC_STATUS_WORD_READ, i);
	}

	if(!flag)
		return ERR_TIME_OUT;


	HIA = (BC_STATUS_WORD_READ >> 0xA) & 0x01;

	if(HIA != 1) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag HIA: the value expected was 1, the value read is %x***",
				HIA);

		snprintf(this->strError, MAX_BUF_SIZE,
				"***Error: flag HIA: the value expected was 1, the value read is %x***.",
				HIA);

		vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_HANDOVER_RESET", hexadecimal), 0x01);
		return ERR_HIACT_LODEM_HIA;
	}

	LOA = (BC_STATUS_WORD_READ >> 0xB) & 0x01;
	if(LOA != 1) {
		Logger::getLogger()->Log(INFO_LEVEL,
				"***Error: flag LOA: the value expected was 1, the value read is %x***",
				LOA);

		snprintf(this->strError, MAX_BUF_SIZE,
				"****Error: flag LOA: the value expected was 1, the value read is %x***",
				LOA);

		vmeDev->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_HANDOVER_RESET", hexadecimal), 0x01);
		return ERR_HIACT_LODEM_HIA;

	}

	usleep(MSEC_TO_USEC(100));

	//SET
	vmeDev->write(HANDOVER_CONTROL_WORD_REG, 0x3);

	Logger::getLogger()->Log(INFO_LEVEL, "***End HIACT_LODEM**");

	return TEST_OK;
}


//UINT8 HIACT_LODEM::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {
//
//	Logger::getLogger()->Log(INFO_LEVEL, "***Start HIACT LODEM***");
//
////	va_list argP;
////	va_start(argP, num_argomenti);
////	int step = va_arg(argP, int);
////	va_end(argP);
//
//	BASE_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->base_address;
//	UINT32 DIRECT_IO = GlobalData::instance()->GetInterfaceData(bt)->direct_io;
//
//	if( bt == STIMP_AVIONIC_3910)
//	{
//		HANDOVER_STATUS_WORD_REG = DIRECT_IO + DEF_AVIONIC_HO + 0x8;
//		BC_STATUS_INTERRUPT_REG = DIRECT_IO + DEF_AVIONIC_HO;
//	}
//	else
//	{
//		HANDOVER_STATUS_WORD_REG = DIRECT_IO + DEF_ATTACK_HO + 0x8;
//		BC_STATUS_INTERRUPT_REG = DIRECT_IO + DEF_ATTACK_HO;
//	}
//
//
//
//	HandoverReg handOver;
//
//	//MCL
//	vmeDev->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0x1);
//	usleep(MSEC_TO_USEC(500));
//
//	//TEST
//	vmeDev->read(HANDOVER_STATUS_WORD_REG, BC_STATUS_WORD_READ);
//
//	HIA = (BC_STATUS_WORD_READ >> 0x9) & 0x01;
//
//	if(HIA != 1) {
//		Logger::getLogger()->Log(INFO_LEVEL,
//				"***Error: flag HIA: the value expected was 1, the value read is %x***",
//				HIA);
//
//		snprintf(this->strError, MAX_BUF_SIZE,
//					"***Error: flag HIA: the value expected was 1, the value read is %x***.",
//					HIA);
//
//		vmeDev->writeConf(VME_HANDOVER_RESET, 0x01);
//		return ERR_HIACT_LODEM_HIA;
//	}
//
//	LOA = (BC_STATUS_WORD_READ >> 0xA) & 0x01;
//	if(LOA != 1) {
//		Logger::getLogger()->Log(INFO_LEVEL,
//				"***Error: flag LOA: the value expected was 1, the value read is %x***",
//				LOA);
//
//		snprintf(this->strError, MAX_BUF_SIZE,
//				"****Error: flag LOA: the value expected was 1, the value read is %x***",
//				LOA);
//
////		vmeDev->writeConf(VME_HANDOVER_RESET, 0x01);
////		return ERR_HIACT_LODEM_LOA;
//	}
//
//
//
//	//SET
//	handOver.raw32 = 0x0;
//
//	handOver.reg.LOADM_ALT = 0x01;
//	handOver.reg.LODEM_NLT = 0x01;
//	handOver.reg.HIACT_ALT = 0x01;
//	handOver.reg.HIACT_NLT = 0x01;
//
//	vmeDev->writeConf(VME_HANDOVER_REG, handOver.raw32);
//
//
//	//TEST
//	vmeDev->read(HANDOVER_STATUS_WORD_REG, BC_STATUS_WORD_READ);
//
//	HIA = (BC_STATUS_WORD_READ >> 0x9) & 0x01;
//	if(HIA != 0) {
//		Logger::getLogger()->Log(INFO_LEVEL,
//							"***Error: flag HIA: the value expected was 0, the value read is %x***",
//							HIA);
//		snprintf(this->strError, MAX_BUF_SIZE,
//							"***Error: flag HIA: the value expected was 0, the value read is %x***.",
//							HIA);
//
//		vmeDev->writeConf(VME_HANDOVER_RESET, 0x01);
//		return ERR_HIACT_LODEM_HIA;
//	}
//
//	LOA = (BC_STATUS_WORD_READ >> 0xA) & 0x01;
//	if(LOA != 0) {
//		Logger::getLogger()->Log(INFO_LEVEL,
//							"***Error: flag LOA: the value expected was 0, the value read is %x***",
//							LOA);
//		snprintf(this->strError, MAX_BUF_SIZE,
//						"****Error: flag LOA: the value expected was 0, the value read is %x***",
//						LOA);
//
//		vmeDev->writeConf(VME_HANDOVER_RESET, 0x01);
//		return ERR_HIACT_LODEM_LOA;
//	}
//
//
//	IP = (BC_STATUS_WORD_READ >> 13) & 0x3;
//
//
//	Logger::getLogger()->Log(INFO_LEVEL,
//								"***IP read is %x***",
//								IP);
//
//	switch(IP)
//	{
//		case 0x0:
//			BC_STATUS_INTERRUPT_REG += 0x6;
//		break;
//
//		case 0x1:
//			BC_STATUS_INTERRUPT_REG += 0x0;
//		break;
//
//		case 0x2:
//			BC_STATUS_INTERRUPT_REG += 0x2;
//		break;
//
//		case 0x3:
//			BC_STATUS_INTERRUPT_REG += 0x4;
//		break;
//
//	}
//
//
//	vmeDev->read(BC_STATUS_INTERRUPT_REG, BC_CONTROL_WORD_READ);
//
//
//	INT_HIACT = (BC_CONTROL_WORD_READ >> 0x9) & 0x1;
//	if(INT_HIACT != 1) {
//		Logger::getLogger()->Log(INFO_LEVEL,
//							"***Error: HIACT INTERRUPT: the value expected was 1, the value read is %x***",
//							INT_HIACT);
//		snprintf(this->strError, MAX_BUF_SIZE,
//				"***Error: HIACT INTERRUPT: the value expected was 1, the value read is %x***",
//				INT_HIACT);
//
//		vmeDev->writeConf(VME_HANDOVER_RESET, 0x01);
//		return ERR_HIACT_LODEM_HIA;
//	}
//
//	INT_LODEM = (BC_CONTROL_WORD_READ & 0xA) & 0x1;
//
//	if(INT_LODEM != 1) {
//		Logger::getLogger()->Log(INFO_LEVEL,
//							"***Error: LODEM INTERRUPT: the value expected was 1, the value read is %x***",
//							INT_LODEM);
//
//		snprintf(this->strError, MAX_BUF_SIZE,
//				"***Error: LODEM INTERRUPT: the value expected was 1, the value read is %x***",
//				INT_LODEM);
//
//		vmeDev->writeConf(VME_HANDOVER_RESET, 0x01);
//		return ERR_HIACT_LODEM_LOA;
//	}
//
//
//	//TEST
//	vmeDev->read(HANDOVER_STATUS_WORD_REG, BC_STATUS_WORD_READ);
//	HIA = (BC_STATUS_WORD_READ >> 0x9) & 0x1;
//	if(HIA != 1) {
//		Logger::getLogger()->Log(INFO_LEVEL,
//				"***Error: flag HIA: the value expected was 1, the value read is %x***",
//				HIA);
//
//		snprintf(this->strError, MAX_BUF_SIZE,
//						"***Error: flag HIA: the value expected was 1, the value read is %x***",
//						HIA);
//		vmeDev->writeConf(VME_HANDOVER_RESET, 0x01);
//		return ERR_HIACT_LODEM_HIA;
//	}
//
//	LOA = (BC_STATUS_WORD_READ >> 0xA) & 0x1;
//	if(LOA != 1) {
//		Logger::getLogger()->Log(INFO_LEVEL,
//				"***Error: flag LOA: the value expected was 1, the value read is %x***",
//				LOA);
//		snprintf(this->strError, MAX_BUF_SIZE,
//						"***Error: flag LOA: the value expected was 1, the value read is %x***",
//						LOA);
//
//		vmeDev->writeConf(VME_HANDOVER_RESET, 0x01);
//		return ERR_HIACT_LODEM_LOA;
//	}
//
//	vmeDev->writeConf(VME_HANDOVER_RESET, 0x01);
//
//	Logger::getLogger()->Log(INFO_LEVEL, "***End HIACT LODEM***");
//
//	return TEST_OK;
//}
//
//
//
