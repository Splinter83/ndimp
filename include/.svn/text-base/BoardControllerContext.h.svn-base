/*
 * SimpStimpProject: BoardControllerContext.h
 *
 *  Created on: 02/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef BOARDCONTROLLERCONTEXT_H_
#define BOARDCONTROLLERCONTEXT_H_

#include "GenericBaseContext.h"
#include "BoardEventsList.h"
#include "GenericEventListener.h"

class I_TSAP;
class VmeAbstractionDevice;
class I_VmeAdapter;

class BoardControllerContext :
	public GenericBaseContext<tBoardControlListenableEventList>,
	public MultipleNotifier<tBoardControlNotifableEventList>{
public:
	BoardControllerContext();
	virtual ~BoardControllerContext();

	void CreateSimpInterface();
	void CreateStimpInterface();
	void CreateGenericInterface();

	I_TSAP * getBoardInterafce() const;

protected:
	I_TSAP *_pBoard;
	VmeAbstractionDevice *_pVmeAbstractDevice;
	I_VmeAdapter *_pVmeAdapter;
	void CleanContext();
};

inline I_TSAP * BoardControllerContext::getBoardInterafce() const{
	return this->_pBoard;
}

#endif /* BOARDCONTROLLERCONTEXT_H_ */
