/*
 * SimpStimpProject: BoardControllerActiveContext.h
 *
 *  Created on: 05/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef BOARDCONTROLLERACTIVECONTEXT_H_
#define BOARDCONTROLLERACTIVECONTEXT_H_

#include "GenericActiveEventListener.h"
#include "BoardControllerContext.h"

class BoardControllerActiveContext : public ActiveMultipleListener<tBoardControlListenableEventList>,
									 public InterfaceImplementation<NotifierElement, tBoardControlNotifableEventList, NotifierElementBase<tBoardControlNotifableEventList> >{
public:
	BoardControllerActiveContext(BoardControllerContext *component):
		ActiveMultipleListener<tBoardControlListenableEventList>(component, "BoardControllerContext"),
		_Component(component){
			assert(_Component);
	}

	virtual ~BoardControllerActiveContext(){
		this->Stop();
	}

	I_TSAP * getBoardInterafce() const{
		return _Component->getBoardInterafce();
	}

protected:
	IMultipleNotifier<tBoardControlNotifableEventList> * GetNotifier(){
		return _Component;
	}

private:
	BoardControllerContext *_Component;
};

#endif /* BOARDCONTROLLERACTIVECONTEXT_H_ */
