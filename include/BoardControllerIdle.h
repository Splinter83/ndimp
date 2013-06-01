/*
 * SimpStimpProject: BoardControllerIdle.h
 *
 *  Created on: 01/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef BOARDCONTROLLERIDLE_H_
#define BOARDCONTROLLERIDLE_H_

#include "Singleton.h"
#include "GenericBaseState.h"
#include "BoardEventsList.h"


class BoardControllerIdle;


class BoardControllerIdle :
	public Singleton<BoardControllerIdle, CreateThreadSafe>,
	public GenericBaseState<tBoardControlListenableEventList> {

	SINGLETON_THREAD_SAFE

public:

	virtual ~BoardControllerIdle();

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

private:

	BoardControllerIdle();

};

//typedef Singleton<BoardControllerIdle, CreateThreadSafe> S_BoardControllerIdle;

#endif /* BOARDCONTROLLERIDLE_H_ */
