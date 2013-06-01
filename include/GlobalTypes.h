/*
 * SimpStimpProject: GlobalTypes.h
 *
 *  Created on: 09/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef GLOBALTYPES_H_
#define GLOBALTYPES_H_

#include "Singleton.h"
#include "memoria.h"
#include "global_types.h"
#include <map>

typedef enum{
	RT_A = 0,
	RT_B
}RemoteTerminalSide;

class GlobalData : public Singleton<GlobalData, CreateThreadSafe>{

	SINGLETON_THREAD_SAFE

typedef ConfigStruct Config;

public:
	virtual ~GlobalData();

	void AddInterface(const Config&);
	interfaccia* GetInterfaceData(const BoardInterfaceType&);
	bool GetDiscreteStatus(const EN_DISCRETE_STATUS &disc);
	void SetDiscreteStatus(const EN_DISCRETE_STATUS &disc,const bool &status);
	void SetRemoteTerminalAddr(const UINT8 &addr, const RemoteTerminalSide& side);
	UINT8 GetRemoteTerminalAddr(const RemoteTerminalSide& side) const;

private:
	GlobalData();
	std::map<BoardInterfaceType,interfaccia*> _interfaceMap;
	DiscreteReg _discrteStatuVectM;
	UINT8 _remoteTermAddr_SideA;
	UINT8 _remoteTermAddr_SideB;
};

inline UINT8 GlobalData::GetRemoteTerminalAddr(const RemoteTerminalSide& side) const {
		if(side == RT_A)
			return _remoteTermAddr_SideA;
		else
			return _remoteTermAddr_SideB;
}

inline void GlobalData::SetRemoteTerminalAddr(const UINT8 &addr, const RemoteTerminalSide& side){
	if(side == RT_A)
		_remoteTermAddr_SideA = addr;
	else
		_remoteTermAddr_SideB = addr;
}

#endif /* GLOBALTYPES_H_ */
