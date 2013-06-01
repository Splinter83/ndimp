#include "OptimizedRefined.h"

#include "Logger.h"
#include <string>
#include <time.h>
#include "Singleton.h"
#include "ConfigFile.h"

OptimizedRefined::OptimizedRefined(I_VmeAdapter *handler) {
	imp = handler;
	initDevice();
}

OptimizedRefined::~OptimizedRefined(){
	imp->closeDevice();
}

void OptimizedRefined::initDevice() {
	try {
		imp->initBoard();
		Logger::getLogger()->Log(INFO_LEVEL,"VME BOARD INIT OK");
	} catch (std::string &str) {
		Logger::getLogger()->Log(FATAL_LEVEL, str.c_str());
		throw str;
	}
}

void OptimizedRefined::read(const UINT32 &address, UINT32 &data,
		const EN_VME_READWRITE_SIZE &mode) {
	try{
		switch (mode) {
		case EN_VME_WORD:
			data = imp->read16(address);
			Logger::getLogger()->Log(DEBUG_LEVEL, "READ VALUE 0x%04x at address 0x%08x", data, address);
			break;
		case EN_VME_BYTE:
			data = imp->read8(address);
			Logger::getLogger()->Log(DEBUG_LEVEL, "READ VALUE 0x%02x at address 0x%08x", data, address);
			break;
		case EN_VME_TRIPLE_BYTE:
			data = imp->read24(address);
			Logger::getLogger()->Log(DEBUG_LEVEL, "READ VALUE 0x%06x at address 0x%08x", data, address);
			break;
		case EN_VME_DOUBLE_WORD:
			data = imp->read32(address);
			Logger::getLogger()->Log(DEBUG_LEVEL, "READ VALUE 0x%08x at address 0x%08x", data, address);
			break;
		default:
			Logger::getLogger()->Log(ERROR_LEVEL, "Unknown read mode value %d",
					mode);
			break;
		}
	}
	catch(std::string &str) {
		Logger::getLogger()->Log(FATAL_LEVEL, str.c_str());
		throw str;
	}
}

void OptimizedRefined::write(const UINT32 &address, const UINT32 &data,
		const EN_VME_READWRITE_SIZE &mode) {
	try{
		switch (mode) {
		case EN_VME_WORD:
			imp->write16(address, data & 0xFFFF);
			break;
		case EN_VME_BYTE:
			Logger::getLogger()->Log(DEBUG_LEVEL, "WRITE VALUE 0x%02x AT 0x%08x", data, address);
			imp->write8(address, data & 0xFF);
			break;
		case EN_VME_TRIPLE_BYTE:
			imp->write24(address, data & 0xFFFFFF);
			break;
		case EN_VME_DOUBLE_WORD:
			imp->write32(address, data);
			break;
		default:
			Logger::getLogger()->Log(ERROR_LEVEL, "Unknown write mode value %d",
					mode);
			break;
		}
	}
	catch(std::string &str) {
		Logger::getLogger()->Log(FATAL_LEVEL, str.c_str());
		throw str;
	}
}

void OptimizedRefined::readConf(const UINT16 &address, UINT32 &data){
	try{
		data = imp->readRegister(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT32>("VME_CONF_BASE_ADDRESS", hexadecimal) + address);
		//Logger::getLogger()->Log(DEBUG_LEVEL, "READ VALUE 0x%08x at address 0x%08x", data,address);
	}
	catch(std::string &str) {
		Logger::getLogger()->Log(FATAL_LEVEL, str.c_str());
		throw str;
	}
}


void OptimizedRefined::writeConf(const UINT16 &address,const UINT32 &data){
	try{
		imp->writeRegister(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT32>("VME_CONF_BASE_ADDRESS", hexadecimal)+ address, data);
	}
	catch(std::string &str) {
		Logger::getLogger()->Log(FATAL_LEVEL, str.c_str());
		throw str;
	}
}

void OptimizedRefined::waitInterrupt(ExternalCallBack callback, const UINT32 &time){
	imp->waitInterrupt(time * (clock()/(float)(1000000L)));
	callback;
}


void OptimizedRefined::readInterruptStatus(UINT32 *status){
	imp->readInterruptStatus(status);
}
