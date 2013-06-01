/*
 * DiscreteManager.cpp
 *
 *  Created on: 12/nov/2012
 *      Author: galileo
 */

#include "DiscreteManager.h"
#include "Logger.h"
#include "global_definitions.h"
#include "Singleton.h"
#include "ConfigFile.h"

DiscreteManager::DiscreteManager() {
	// TODO Auto-generated constructor stub

}

DiscreteManager::~DiscreteManager() {
	// TODO Auto-generated destructor stub
}

void* DiscreteManager::run(){
	UINT32 interruptActive;
	UINT32 currentStatus;
	DiscreteReg simpDiscrete;
	Mil1553Reg stimpDiscrete;

	while(!_isStopped){
		_adapter->readConf(Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("VME_CONF_BASE_ADDRESS", hexadecimal) + Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<UINT8>("VME_DISCRETE_IO_ADDRESS", hexadecimal),currentStatus);
		_adapter->waitInterrupt(NULL,1000);
		_adapter->readInterruptStatus(&interruptActive);
		switch(_board_type){
			case SIMP1:
			case SIMP2:
				currentStatus ^= interruptActive;
			break;

			case STIMP:
			break;

			default:
				Logger::getLogger()->Log(DEBUG_LEVEL,"Board type unknown in DiscreteManager");
			return NULL;
		}
	}
}

