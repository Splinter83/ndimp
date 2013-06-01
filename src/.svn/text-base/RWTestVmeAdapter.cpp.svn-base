/*
 * RWTestVmeAdapter.cpp
 *
 *  Created on: 11/giu/2012
 *      Author: emanuele_galli
 */

#include "RWTestVmeAdapter.h"
#include "Logger.h"
#include "Singleton.h"
#include "ConfigFile.h"

RW_TestVmeAdapter::RW_TestVmeAdapter() {
	// TODO Auto-generated constructor stub

}

RW_TestVmeAdapter::~RW_TestVmeAdapter() {
	// TODO Auto-generated destructor stub
}

void RW_TestVmeAdapter::initBoard() throw(std::string) {
	Logger::getLogger()->Log(INFO_LEVEL,"Init VME board");
}

void RW_TestVmeAdapter::closeDevice(){
	Logger::getLogger()->Log(INFO_LEVEL,"Close VME board");
}

void RW_TestVmeAdapter::write8(UINT32 regAddress, UINT8 value) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "WRITE_08 0x%02x at 0x%08x", value, regAddress);
}

void RW_TestVmeAdapter::write16(unsigned int regAddress, unsigned short value) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "WRITE_16 0x%04x at 0x%08x", value, regAddress);
}

void RW_TestVmeAdapter::write24(UINT32 regAddress, UINT32 value) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "WRITE_24 0x%06x at 0x%08x", value, regAddress);
}

void RW_TestVmeAdapter::write32(unsigned int regAddr, unsigned int val) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "WRITE_32 0x%08x at 0x%08x",val, regAddr);
}

UINT8 RW_TestVmeAdapter::read8(UINT32 regAddr32) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "READ_08 at 0x%08x", regAddr32);
	return 0x0000;
}

unsigned short RW_TestVmeAdapter::read16(unsigned int regAddr16) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "READ_16 at 0x%08x", regAddr16);
	return 0x0000;
}

UINT32 RW_TestVmeAdapter::read24(UINT32 regAddr32) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "READ_24 at 0x%08x", regAddr32);
	return 0x0000;
}

unsigned int RW_TestVmeAdapter::read32(unsigned int regAddr32) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "READ_32 at 0x%08x", regAddr32);
	return 0x0000;
}


UINT32 RW_TestVmeAdapter::readRegister(UINT32 regAddr) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "READ_REGISTER at 0x%08x", regAddr);
	if ( regAddr == 0x20000024) // board selection register
		return ( 0x0001 << 4 ); // simp
	return 0x0000;
}


void RW_TestVmeAdapter::writeRegister(UINT32 regAddr, UINT32 val) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "WRITE_REGISTER 0x%06x at 0x%08x", val, regAddr);
}

void RW_TestVmeAdapter::readInterruptStatus(UINT32* status) throw(std::string){
	Logger::getLogger()->Log(INFO_LEVEL, "VME_INTERRUPT_RESET: 0x%06x at 0x%08x", 0, Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_INTERRUPT_RESET", hexadecimal));
}

void RW_TestVmeAdapter::waitInterrupt(const UINT32 &time) throw(int){
	Logger::getLogger()->Log(INFO_LEVEL, "Wait interrupt error");
}
