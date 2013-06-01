//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : TSAP.cpp
//  @ Date : 08/06/2012
//  @ Author : 
//
//


#include "TSAP.h"
#include "OptimizedRefined.h"
#include "OptimizedVmeAdapter.h"
#include "TestInclude.h"
#include "GlobalTypes.h"
#include "Logger.h"
#include "Utils.h"
#include "Singleton.h"
#include "ConfigFile.h"

#include <assert.h>

#define VME_CONF_MAX_ADDRESS  (VME_CONF_BASE_ADDRESS + 0x100)
#define VME_OPT_BASE_ADDRESS  0x28000000
#define RAM_SIZE 0xDFFFFFFF


#define TEST_VME

TSAP::TSAP(VmeAbstractionDevice *adapter) : I_TSAP(adapter)
{
	_sgaAddress.raw32 = 0;
	_baseAddress = VME_OPT_BASE_ADDRESS;
	_ramSize = RAM_SIZE;
	adapter->readConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_SGA_ADDRESS", hexadecimal),_sgaAddress.raw32);
}

TSAP::TSAP(VmeAbstractionDevice *adapter,  unsigned int addr, unsigned int size) :
	I_TSAP(adapter),
	_baseAddress(addr),
	_ramSize(size)
{
	adapter->readConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_SGA_ADDRESS", hexadecimal),_sgaAddress.raw32);
}

TSAP::~TSAP(){
	if(vmeAdapter == NULL)
		delete vmeAdapter;
	vmeAdapter = 0;
}

unsigned int TSAP::read(unsigned int address, const EN_VME_READWRITE_SIZE& align) {
	UINT32 data;
	if(address >= Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) && address <= Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal)){
		vmeAdapter->readConf(address & 0xFFFF, data);
		return data;
	}
	switch(align){
		case EN_VME_BYTE:
			vmeAdapter->read(address,data,EN_VME_BYTE);
		break;
		case EN_VME_WORD:
			vmeAdapter->read(address,data);
		break;
		case EN_VME_DOUBLE_WORD:
			vmeAdapter->read(address,data,EN_VME_DOUBLE_WORD);
		break;
		default:
			throw "Unknown Alignment";
		break;
	}
	return data;
}

void TSAP::write(UINT32 data, UINT32 address, const EN_VME_READWRITE_SIZE& align) {
	if(address >= Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) && address <= Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal)){
		vmeAdapter->writeConf(address & 0xFFFF, data);
	}
	switch(align){
		case EN_VME_BYTE:
			vmeAdapter->write(address,data,EN_VME_BYTE);
		break;
		case EN_VME_WORD:
			vmeAdapter->write(address,data);
		break;
		case EN_VME_DOUBLE_WORD:
			vmeAdapter->write(address,data,EN_VME_DOUBLE_WORD);
		break;
		default:
			throw "Unknown Alignment";
		break;
	}
}

UINT32 TSAP::execTest(const TestStruct& test) {
	return 0;
}

void TSAP::initBoard() {
//TODO
}

AllDiscreteType TSAP::readAllDiscrete(){
	AllDiscreteType discrete;
	discrete.discrete_reg.raw32 = 0;
try{
    discrete.general_config_reg.raw32 = this->read(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT32>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),EN_VME_DOUBLE_WORD);
	//discrete.discrete_reg.raw32 = this->read(VME_CONF_BASE_ADDRESS + VME_DISCRETE_IO_ADDRESS,EN_VME_DOUBLE_WORD);
/*
	discrete.mil1553_reg.raw32 = this->read(VME_CONF_BASE_ADDRESS + VME_1553_ADDRESS,EN_VME_DOUBLE_WORD);
	discrete.handover_reg.raw32 = this->read(VME_CONF_BASE_ADDRESS + VME_HANDOVER_REG,EN_VME_DOUBLE_WORD);
	discrete.sga_reg.raw32 = this->read(VME_CONF_BASE_ADDRESS + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT32>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT32>("VME_SGA_ADDRESS", hexadecimal),EN_VME_DOUBLE_WORD);
	discrete.rt_reg.raw32 = this->read(VME_CONF_BASE_ADDRESS + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT32>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT32>("VME_REMOTE_TERM_ADDRESS", hexadecimal),EN_VME_DOUBLE_WORD);
	discrete.fofe_reg.raw32 = this->read(VME_CONF_BASE_ADDRESS + VME_FOFE_ADDRESS,EN_VME_DOUBLE_WORD);
*/
}
catch(UINT8 & error){
	Logger::getLogger()->Log(DEBUG_LEVEL,"Read Error in readAllDiscrete");
}
	return discrete;
}

void TSAP::initTSAPBoard() {

}


UINT32 TSAP::execCommonTest(const TestStruct& test){
	I_TEST* iTest;
	UINT32 res = 1;
	GeneralConfigReg config;
	UINT32 currentConfig;
	vmeAdapter->readConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),currentConfig);
	config.raw32 = currentConfig;
	config.reg.ENWDEXT = 0; /* Deve essere 0 */
	config.reg.ENWDLS = 0; /* Deve essere 0 */

	switch(test._testNumber){
		case EN_OPTIMIZED_BUS: //I/F Optimized Bus Test
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new IF_Optimized_Bus_Test();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
		break;
		case EN_RAM: //RAM Test
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new RAM_Test();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
		break;
		case EN_SKELETON_3838: // Test Skeleton RT/BC 3910
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new Skeleton();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
		break;
		case EN_HS_SELFTEST: // HS Selftest
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new HS_Selftest();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
		break;
		case EN_LOOPBACK_A: // External Loopback Ch A
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new Loopback_Esterno();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId,2, 'a', false);
		break;
		case EN_LOOPBACK_B: // External Loopback Ch B
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new Loopback_Esterno();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId,2, 'b', false);
		break;
		case EN_LOOPBACK_LS_A: // External Loopback Ch A activated by LS
			if(test._step == 1){
				vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
				vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
				usleep(SEC_TO_USEC(2));
			}
			iTest = new Loopback_Esterno_Att_LS();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId,1, 'a',test._step);
		break;
		case EN_LOOPBACK_LS_B: //External Loopback Ch B activated by LS
			if(test._step == 1){
				vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
				vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
				usleep(SEC_TO_USEC(2));
			}
			iTest = new Loopback_Esterno_Att_LS();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId,1, 'b',test._step);
		break;
		case EN_HS_INTERRUPT_POINTER: // Test HS Interrupt Pointer Offset
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new HS_Interrupt_Pointer_Offset();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
		break;
		case EN_LS_SELFTEST: // LS 3910 Selftest
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new Selftest();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
		break;
		case EN_RT_ADDRESS: // RT 3910 Address Test
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new Address_Test();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
		break;
		case EN_RT_PARITY: // RT 3910 Parity Test
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new Parity_Test();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
		break;
		case EN_LS_RXTX:
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new Selftest();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
			delete iTest;
			if(res != TEST_OK){
				strcpy(this->errorMessage,iTest->getError());
				return res*10;
			}
			iTest = new Inizializzazione_LS();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);
			delete iTest;
			if(res != TEST_OK){
				strcpy(this->errorMessage,iTest->getError());
				return res*100;
			}
			iTest = new Iniz_Tavola_Descr_SA_01_RX();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId,1,0);
			delete iTest;
			if(res != TEST_OK){
				strcpy(this->errorMessage,iTest->getError());
				return res*1000;
			}
			iTest = new Iniz_Tavola_Descr_SA_01_TX();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId,1,0);
		break;
		case EN_SKELETON_BUS:
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new Skeleton_Test();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId,1,test._step);
		break;
		case EN_INTERRUPT:
			if(test._step == 1){
				vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
				vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
				usleep(SEC_TO_USEC(2));
			}
			iTest = new Interrupt_LS_Test();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId,1,test._step);
		break;
		case EN_BIT_HISTORY:
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_GENERAL_CONF_ADDRESS", hexadecimal),config.raw32);
			vmeAdapter->writeConf(Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_MCL_REG", hexadecimal),0); // Master Clear
			usleep(SEC_TO_USEC(2));
			iTest = new BitHistory_Test();
			iTest->setDevice(vmeAdapter);
			res = iTest->execTest(test._configId);

		break;
		default:
			strcpy(this->errorMessage,"Unknown Test Received");
		return res;
	}
	if(res > NEXT_STEP){
		strcpy(this->errorMessage,iTest->getError());
	}
	delete iTest;
	return res;
}

void TSAP::setupRemoteTerminal(){
	RT_Reg reg;
	UINT8 rt_a = GlobalData::instance()->GetRemoteTerminalAddr(RT_A);
	UINT8 rt_b = GlobalData::instance()->GetRemoteTerminalAddr(RT_B);
	reg.raw32 = 0;
	if( rt_a!= 0xFF && vmeAdapter != NULL){
		rt_a -= 1;
		reg.raw32 = (rt_a << 8);
		reg.reg.RTA_A_SEL_W = 1;
		reg.reg.RTP_A_W = Utils::CalcOddParity(rt_a << 8);
		vmeAdapter->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal),reg.raw32);
	}
	else if(rt_b != 0xFF && vmeAdapter != NULL){
		rt_b -= 1;
		reg.raw32 = (rt_b << 1);
		reg.reg.RTA_B_SEL_W = 1;
		reg.reg.RTP_B_W = Utils::CalcOddParity(rt_a << 8);
		vmeAdapter->writeConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_REMOTE_TERM_ADDRESS", hexadecimal),reg.raw32);
	}
}


