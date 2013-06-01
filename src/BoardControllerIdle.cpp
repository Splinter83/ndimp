/*
 * SimpStimpProject: BoardControllerIdle.cpp
 *
 *  Created on: 01/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "BoardControllerIdle.h"
#include "BoardControllerActive.h"
#include "BoardControllerContext.h"
#include "BoardControllerError.h"
#include "Logger.h"
#include "DiscreteManager.h"
#include "I_TSAP.h"


BoardControllerIdle::BoardControllerIdle() {
}

BoardControllerIdle::~BoardControllerIdle() {

}

void BoardControllerIdle::Handle(const IdleEvent & msg){
    Logger::getLogger()->Log(DEBUG_LEVEL, "Idle Event received in idle state");
}

void BoardControllerIdle::Handle(const ActiveEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Active Event receive in idle state");
	switch(msg.config){
		case SIMP1 :
			dynamic_cast<BoardControllerContext*>(this->GetContext())->CreateSimpInterface();
			DiscreteManager::instance()->setBoardTpe(SIMP1);
		break;
		case SIMP2 :
			dynamic_cast<BoardControllerContext*>(this->GetContext())->CreateSimpInterface();
			DiscreteManager::instance()->setBoardTpe(SIMP2);
		break;
		case STIMP :
			dynamic_cast<BoardControllerContext*>(this->GetContext())->CreateStimpInterface();
			DiscreteManager::instance()->setBoardTpe(STIMP);
		break;
		case OTHER :
			dynamic_cast<BoardControllerContext*>(this->GetContext())->CreateGenericInterface();
		break;
	}
	ChangeState(BoardControllerActive::instance());
}

void BoardControllerIdle::Handle(const ErrorEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Error Event received in idle state");
	ChangeState(BoardControllerError::instance());
}

void BoardControllerIdle::Handle(const ShutdownEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Shutdown Event received in idle state");
}

void BoardControllerIdle::Handle(const SGA_Event & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "SGA Event received in idle state");
}

void BoardControllerIdle::Handle(const WriteEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL,
			"Write Event received in Idle state");
	BoardControllerContext* context =
			dynamic_cast<BoardControllerContext*>(this->GetContext());

	if(context->getBoardInterafce() == NULL)
		context->CreateGenericInterface();

	ResultStruct res;
	res.CurrentStep = 1;
	res.IsTerminated = true;
	try {
		context->getBoardInterafce()->write(msg._data, msg._address,
				msg._align);
		res.Result = 0;
		res.CommandSuccess = true;
	} catch (const std::string &err) {
		res.Result = 1;
		res.CommandSuccess = false;
		strcpy(res.ErrorStr, err.c_str());
	}
	context->NotifyListeners(CommandResultEvent(res));
}

void BoardControllerIdle::Handle(const ReadEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Read Event received in idle state");

	BoardControllerContext* context =
			dynamic_cast<BoardControllerContext*>(this->GetContext());

	if(context->getBoardInterafce() == NULL)
		context->CreateGenericInterface();

	ResultStruct res;
	res.CurrentStep = 1;
	res.IsTerminated = true;
	try {
		UINT32 data = context->getBoardInterafce()->read(msg._address,
				msg._align);
		res.Result = data;
		res.CommandSuccess = true;
	} catch (const std::string &err) {
		res.Result = -1;
		res.CommandSuccess = false;
		strcpy(res.ErrorStr, err.c_str());
	}
	context->NotifyListeners(CommandResultEvent(res));
}

void BoardControllerIdle::Handle(const TestsReqEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Test Request Event received in idle state");
}

void BoardControllerIdle::Handle(const ConfigEvent & msg){
	Logger::getLogger()->Log(DEBUG_LEVEL, "Configuration Event received in idle state");
}

void BoardControllerIdle::Handle(const DiscreteEvent & msg){

}
