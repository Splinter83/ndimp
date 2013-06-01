/*
 * SimpStimpProject: BoardControllerContext.cpp
 *
 *  Created on: 02/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "BoardControllerContext.h"
#include "global_definitions.h"
#include "BoardControllerIdle.h"
#include "BoardControllerActive.h"
#include "STIMP.h"
#include "TSAP.h"
#include "SIMP.h"
#include "OptimizedRefined.h"
#include "VmeAbstractionDevice.h"
#include "I_VmeAdapter.h"
#include "DiscreteManager.h"
#ifdef VME_PRESENT
	#include "OptimizedVmeAdapter.h"
#else
	#include "RWTestVmeAdapter.h"
#endif


BoardControllerContext::BoardControllerContext() :
						_pBoard(NULL),
						_pVmeAbstractDevice(NULL),
						_pVmeAdapter(NULL){
	// TODO Auto-generated constructor stub
	IGenericState<tBoardControlListenableEventList> * state = NULL;

	state = BoardControllerIdle::instance();
	state->SetContext(this);

	state = BoardControllerActive::instance();
	state->SetContext(this);

	_CurrentState 	= BoardControllerIdle::instance();
	_PreviousState	= NULL;
	_NewState		= _CurrentState;
}

BoardControllerContext::~BoardControllerContext() {
	// TODO Auto-generated destructor stub
	DiscreteManager::instance()->Stop();

	if(_pVmeAbstractDevice == NULL){
		delete _pVmeAbstractDevice;
	}
	_pVmeAbstractDevice = NULL;

	if(_pVmeAdapter == NULL){
		delete _pVmeAdapter;
	}
	_pVmeAdapter = NULL;

	if(_pBoard != NULL)
		delete _pBoard;
	_pBoard = NULL;
}

void BoardControllerContext::CreateSimpInterface(){
	if(_pBoard != NULL){
		CleanContext();
	}
#ifdef VME_PRESENT
	_pVmeAdapter = new OptimizedVmeAdapter();
#else
	_pVmeAdapter = new RW_TestVmeAdapter();
#endif
	_pVmeAbstractDevice = new OptimizedRefined(_pVmeAdapter);
	_pBoard = new SIMP(_pVmeAbstractDevice);
	DiscreteManager::instance()->setVmeAdapter(_pVmeAbstractDevice);
}

void BoardControllerContext::CreateStimpInterface(){
	if(_pBoard != NULL){
		CleanContext();
	}
#ifdef VME_PRESENT
	_pVmeAdapter = new OptimizedVmeAdapter();
#else
	_pVmeAdapter = new RW_TestVmeAdapter();
#endif
	_pVmeAbstractDevice = new OptimizedRefined(_pVmeAdapter);
	_pBoard = new STIMPboard(_pVmeAbstractDevice);
	DiscreteManager::instance()->setVmeAdapter(_pVmeAbstractDevice);
}

void BoardControllerContext::CreateGenericInterface(){
	if(_pBoard != NULL){
		CleanContext();
	}
#ifdef VME_PRESENT
	_pVmeAdapter = new OptimizedVmeAdapter();
#else
	_pVmeAdapter = new RW_TestVmeAdapter();
#endif
	_pVmeAbstractDevice = new OptimizedRefined(_pVmeAdapter);
	_pBoard = new TSAP(_pVmeAbstractDevice);
}

void BoardControllerContext::CleanContext(){
	if(_pVmeAbstractDevice == NULL){
		delete _pVmeAbstractDevice;
	}
	_pVmeAbstractDevice = NULL;

	if(_pVmeAdapter == NULL){
		delete _pVmeAdapter;
	}
	_pVmeAdapter = NULL;

	if(_pBoard != NULL)
		delete _pBoard;
	_pBoard = NULL;
}

