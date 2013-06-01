/*
 * DiscreteManager.h
 *
 *  Created on: 12/nov/2012
 *      Author: galileo
 */

#ifndef DISCRETEMANAGER_H_
#define DISCRETEMANAGER_H_

#include "Singleton.h"
#include "BaseRunnableThread.h"


#include "VmeAbstractionDevice.h"

class DiscreteManager : public Singleton<DiscreteManager, CreateThreadSafe>,
						public BaseRunnableThread{

	SINGLETON_THREAD_SAFE

public:
	virtual ~DiscreteManager();
	void setVmeAdapter(VmeAbstractionDevice *adapter);
	void setBoardTpe(const BoardType &type);
private:
	DiscreteManager();
	void* run();

private:
	VmeAbstractionDevice *_adapter;
	BoardType _board_type;
};

inline void DiscreteManager::setVmeAdapter(VmeAbstractionDevice *adapter){
	_adapter = adapter;
}

inline void DiscreteManager::setBoardTpe(const BoardType &type){
	_board_type = type;
}

#endif /* DISCRETEMANAGER_H_ */
