/*
 * BoardControllerError.cpp
 *
 *  Created on: 18/ott/2012
 *      Author: emanuele_galli
 */

#include "BoardControllerError.h"
#include "Logger.h"

extern bool isSystemStopped;

BoardControllerError::BoardControllerError() {
	// TODO Auto-generated constructor stub

}

BoardControllerError::~BoardControllerError() {
	// TODO Auto-generated destructor stub
}

void BoardControllerError::Handle(const OnEntryEvent & msg){
	isSystemStopped = true;
}

void BoardControllerError::Handle(const IdleEvent & msg){
    Logger::getLogger()->Log(DEBUG_LEVEL, "Idle Event received in error state");
}

void BoardControllerError::Handle(const ActiveEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Active Event receive in error state");
}

void BoardControllerError::Handle(const ErrorEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Error Event received in error state");
}

void BoardControllerError::Handle(const ShutdownEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Shutdown Event received in error state");
}

void BoardControllerError::Handle(const SGA_Event & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "SGA Event received in error state");
}

void BoardControllerError::Handle(const WriteEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Write Event received in error state");
}

void BoardControllerError::Handle(const ReadEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Read Event received in error state");
}

void BoardControllerError::Handle(const TestsReqEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Test Request Event received in error state");
}

void BoardControllerError::Handle(const ConfigEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Configuration Event received in error state");
}

void BoardControllerError::Handle(const DiscreteEvent & msg){

}

