/*
 * SimpStimpProject: GlobalTypes.cpp
 *
 *  Created on: 09/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "GlobalTypes.h"
#include "external_vars.h"

#include <iostream>

#include <string.h>

GlobalData::~GlobalData() {
	// TODO Auto-generated destructor stub
}
GlobalData::GlobalData() {
	_interfaceMap[SIMP1_AVIONIC_3910] = &(interface[SIMP1_AVIONIC_3910]);
	_interfaceMap[SIMP1_BSD_EDDL] = &(interface[SIMP1_BSD_EDDL]);
	_interfaceMap[SIMP1_MDP_EDDL] = &(interface[SIMP1_MDP_EDDL]);
	_interfaceMap[SIMP1_CSMU_EDDL] = &(interface[SIMP1_CSMU_EDDL]);
	_interfaceMap[SIMP2_ATTACK_3910] = &(interface[SIMP2_ATTACK_3910]);
	_interfaceMap[SIMP2_EMU1_EDDL] = &(interface[SIMP2_EMU1_EDDL]);
	_interfaceMap[SIMP2_UCS_3838] = &(interface[SIMP2_UCS_3838]);
	_interfaceMap[SIMP2_EMU2_EDDL] = &(interface[SIMP2_EMU2_EDDL]);
	_interfaceMap[STIMP_AVIONIC_3910] = &(interface[STIMP_AVIONIC_3910]);
	_interfaceMap[STIMP_ATTACK_3910] = &(interface[STIMP_ATTACK_3910]);
	_interfaceMap[UNK_BOARD_TYPE] = &(interface[UNK_BOARD_TYPE]);

	memset(&_discrteStatuVectM,0,sizeof(_discrteStatuVectM));
	_remoteTermAddr_SideA = 0xFF;
	_remoteTermAddr_SideB = 0xFF;
}

void GlobalData::AddInterface(const Config& conf){
	interfaccia *pInterface;
	BoardInterfaceType type;
	RemoteTerminalSide side;
	switch(conf._board){
		case SIMP1:
			switch(conf._interface){
				case AVIONIC:
					type = SIMP1_AVIONIC_3910;
					side = RT_A;
					break;
				case BSD:
					type = SIMP1_BSD_EDDL;
					side = RT_A;
					break;
				case MDP:
					type = SIMP1_MDP_EDDL;
					side = RT_B;
					break;
				case CSMU:
					type = SIMP1_CSMU_EDDL;
					side = RT_B;
					break;
				default:
					std::terminate();
					break;
			}
			//pInterface = _interfaceMap[type];
			pInterface = &(interface[type]);
			strcpy(pInterface->board_name,"SIMP1");
			break;
		case SIMP2:
			switch(conf._interface){
				case ATTACK:
					type = SIMP2_ATTACK_3910;
					side = RT_A;
					break;
				case EMU1:
					type = SIMP2_EMU1_EDDL;
					side = RT_A;
					break;
				case UCS:
					type = SIMP2_UCS_3838;
					side = RT_B;
					break;
				case EMU2:
					type = SIMP2_EMU2_EDDL;
					side = RT_B;
					break;
				default:
					throw "Unknown SIMP2 interface";
					std::terminate();
				break;
			}
			//pInterface = _interfaceMap[type];
			pInterface = &interface[type];
			strcpy(pInterface->board_name,"SIMP2");
			break;
		case STIMP:
			side = RT_A;
			switch(conf._interface){
				case AVIONIC:
					type = STIMP_AVIONIC_3910;
					break;
				case ATTACK:
					type = STIMP_ATTACK_3910;
					break;
				default:
					throw "Unknown STIMP interface";
					std::terminate();
				break;
			}
			//pInterface = _interfaceMap[type];
			pInterface = &interface[type];
			strcpy(pInterface->board_name,"STIMP");
			break;
		case NDIMP:
			// TODO: inserimento def interfaccia NDIMP
			/*
			side = RT_A;
			switch(conf._interface){
				case AVIONIC:
					type = STIMP_AVIONIC_3910;
					break;
				case ATTACK:
					type = STIMP_ATTACK_3910;
					break;
				default:
					throw "Unknown STIMP interface";
					std::terminate();
				break;
			}
			//pInterface = _interfaceMap[type];
			pInterface = &interface[type];
			strcpy(pInterface->board_name,"STIMP");
			*/
			break;
		case OTHER:
			type = UNK_BOARD_TYPE;
			//pInterface = _interfaceMap[type];
			pInterface = &interface[type];
			strcpy(pInterface->board_name,"OTHER");
			break;
		default:
			std::cerr << "Error in  GlobalTypes::AddInterface. Type Unknown" << std::endl;
			throw std::string("GlobalTypes: Unknown Type");
			return;
	}

	pInterface->arbitered_io = conf._arbiteredIO;
	pInterface->base_address = conf._baseAddress;
	pInterface->direct_io = conf._directIO;
	pInterface->memory_size = conf._RamSize;
	pInterface->restart_hs = conf._restartHS;
	pInterface->type = type;
	pInterface->bit_history_addr = conf._bitHistoryAddr;
	pInterface->bit_history_size = conf._bitHistorySize;
	pInterface->side = side;

	if(conf._rtAddress != 0xFF){
		if(side == RT_A)
			_remoteTermAddr_SideA = conf._rtAddress;
		else
			_remoteTermAddr_SideB = conf._rtAddress;
	}
}

interfaccia* GlobalData::GetInterfaceData(const BoardInterfaceType& board){
	return _interfaceMap[board];
}

bool GlobalData::GetDiscreteStatus(const EN_DISCRETE_STATUS &disc){
	return (bool)((_discrteStatuVectM.raw32 >> disc) & 0x1);
}

void GlobalData::SetDiscreteStatus(const EN_DISCRETE_STATUS &disc,const bool &status){
	_discrteStatuVectM.raw32 |= (status << disc);
}
