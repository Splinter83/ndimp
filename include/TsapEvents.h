/*
 * TsapEvents.h
 *
 *  Created on: 04/set/2012
 *  Author: Emanuele Galli
 */

#ifndef TSAPEVENTS_H_
#define TSAPEVENTS_H_

#include <string.h>
#include "global_types.h"
#include <vector>

struct IdleEvent{};

struct ActiveEvent{
	ActiveEvent(const BoardType& conf){
		config = conf;
	}
	BoardType config;
};

struct ErrorEvent{};

struct ShutdownEvent{};

struct RT_ModeEvent{};
struct BC_ModeEvent{};

struct SGA_Event{
	SGA_Event(UINT8 val) : _sga(val){

	}
	UINT8 _sga;
};

struct WriteEvent{
	WriteEvent(UINT32 add,INT32 d, EN_VME_READWRITE_SIZE align) : _address(add), _data(d), _align(align){}
	UINT32 _address;
	INT32 _data;
	EN_VME_READWRITE_SIZE _align;
};

struct ReadEvent{
	ReadEvent(UINT32 add,EN_VME_READWRITE_SIZE align) : _address(add), _align(align){}
	UINT32 _address;
	EN_VME_READWRITE_SIZE _align;
};

struct TestsReqEvent{
	TestsReqEvent(const TestStruct &event){
		memset(&_test,0,sizeof(_test));
		memcpy(&_test,&event,sizeof(_test));
	}
	TestStruct _test;
};

struct ConfigEvent{
	ConfigEvent(const ConfigStruct &event){
		memset(&_config,0,sizeof(_config));
		memcpy(&_config,&event,sizeof(_config));
	}
	ConfigStruct _config;
};

struct SgaEvent{
	SgaEvent(const EN_SGA_ADDRESS &new_sga){
		sga_addr = new_sga;
	}
	EN_SGA_ADDRESS sga_addr;
};

struct CommandResultEvent{
	CommandResultEvent(const ResultStruct &event){
		memset(&_cmdResult,0,sizeof(_cmdResult));
		memcpy(&_cmdResult,&event,sizeof(_cmdResult));
	}
	ResultStruct _cmdResult;
};

struct DiscreteEvent{
	DiscreteEvent(const UINT32 discreteStatus){
		_status = discreteStatus;
	}
	UINT32 _status;
};

#endif /* TSAPEVENTS_H_ */
