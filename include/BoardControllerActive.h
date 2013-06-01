/*
 * SimpStimpProject: BoardControllerActive.h
 *
 *  Created on: 02/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef BOARDCONTROLLERACTIVE_H_
#define BOARDCONTROLLERACTIVE_H_

#include "Singleton.h"
#include "GenericBaseState.h"
#include "BoardEventsList.h"
#include "BaseRunnableThread.h"
#include "TCPClient.h"
#include <map>
#include <string>

class BoardControllerActive;
class I_TSAP;

class BoardControllerActive :
	public Singleton<BoardControllerActive, CreateThreadSafe>,
	public GenericBaseState<tBoardControlListenableEventList>,
	public BaseRunnableThread{

	SINGLETON_THREAD_SAFE

public:
	virtual ~BoardControllerActive();

	void Handle(const OnEntryEvent & msg);
	void Handle(const OnExitEvent & msg);

	virtual void Handle(const IdleEvent & msg);
	virtual void Handle(const ActiveEvent & msg);
	virtual void Handle(const ErrorEvent & msg);
	virtual void Handle(const ShutdownEvent & msg);

	virtual void Handle(const SGA_Event & msg);
	virtual void Handle(const WriteEvent & msg);
	virtual void Handle(const ReadEvent & msg);
	virtual void Handle(const TestsReqEvent & msg);
	virtual void Handle(const ConfigEvent & msg);
	virtual void Handle(const DiscreteEvent & msg);

private: //methods
	BoardControllerActive();
	void* run();

private: //attributes
	std::map<UINT32, std::string> discrete_map;
	std::map<UINT32, std::string> handover_map;
	std::map<UINT32, std::string> general_conf_map;
	bool isReadDiscreteActive;
};

#endif /* BOARDCONTROLLERACTIVE_H_ */
