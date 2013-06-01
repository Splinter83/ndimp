//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : VmeAbstractionDevice.h
//  @ Date : 08/06/2012
//  @ Author : Emanuele Galli
//
//


#if !defined(_VMEABSTRACTIONDEVICE_H)
#define _VMEABSTRACTIONDEVICE_H


#include "global_definitions.h"
#include "global_types.h"
#include "I_VmeAdapter.h"


class VmeAbstractionDevice {
public:
	//VmeAbstractionDevice(I_VmeAdapter<Handler> *handler){imp = handler;}
	virtual ~VmeAbstractionDevice(){}

	virtual void setVmeAdapter(I_VmeAdapter *handler) = 0;
	virtual void read(const UINT32 &address, UINT32 &data, const EN_VME_READWRITE_SIZE &mode = EN_VME_WORD) = 0;
	virtual void write(const UINT32 &address,const UINT32 &data, const EN_VME_READWRITE_SIZE &mode = EN_VME_WORD) = 0;
	virtual void readConf(const UINT16 &address, UINT32 &data) = 0;
	virtual void writeConf(const UINT16 &address,const UINT32 &data) = 0;
	virtual void waitInterrupt(ExternalCallBack callback, const UINT32 &time) = 0;
	virtual void readInterruptStatus(UINT32 *status) = 0;

protected:
	virtual void initDevice() = 0;
	//I_VmeAdapter<Handler> *imp;

};


#endif  //_VMEABSTRACTIONDEVICE_H