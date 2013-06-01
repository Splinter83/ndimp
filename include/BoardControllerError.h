/*
 * BoardControllerError.h
 * Error state board controller
 *
 * Created on: 18/ott/2012
 * Author: Emanuele Galli
 */

#ifndef BOARDCONTROLLERERROR_H_
#define BOARDCONTROLLERERROR_H_

#include "Singleton.h"
#include "GenericBaseState.h"
#include "BoardEventsList.h"

class BoardControllerError;

class BoardControllerError 	:
	public Singleton<BoardControllerError, CreateThreadSafe>,
	public GenericBaseState<tBoardControlListenableEventList>{

	SINGLETON_THREAD_SAFE

public:
	virtual ~BoardControllerError();

	void Handle(const OnEntryEvent & msg);

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
	BoardControllerError();
};

#endif /* BOARDCONTROLLERERROR_H_ */
