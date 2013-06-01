//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : OptimizedRefined.h
//  @ Date : 08/06/2012
//  Author: Emanuele Galli
//   *  Copyright 2012 Sky-Technologies Srl.
//

#ifndef _OPTIMIZEDREFINED_H
#define _OPTIMIZEDREFINED_H

#include "VmeAbstractionDevice.h"

#include "global_definitions.h"

/*!
 * \class OptimizedRefined
 */
class OptimizedRefined: public VmeAbstractionDevice {

public:
	/*!
	 * Constructor
	 * @param handler
	 */
	OptimizedRefined(I_VmeAdapter *handler = 0);

	/*!
	 * Destructor
	 */
	virtual ~OptimizedRefined();

	/*!
	 * Sets VME adapter
	 * @param handler
	 */
	void setVmeAdapter(I_VmeAdapter *handler);

	/*!
	 * Reads a data from VME adapter
	 * @param address
	 * @param data
	 * @param mode
	 */
	void read(const UINT32 &address, UINT32 &data,
			const EN_VME_READWRITE_SIZE &mode = EN_VME_WORD);

	/*!
	 * Writes a data on VME adapter
	 * @param address
	 * @param data
	 * @param mode
	 */
	void write(const UINT32 &address, const UINT32 &data,
			const EN_VME_READWRITE_SIZE &mode = EN_VME_WORD);

	/**
	 * Read data from configuration registers
	 * @param address Register address
	 * @param data Read Data
	 */
	void readConf(const UINT16 &address, UINT32 &data);

	/**
	 * Write data to configuration registers
	 * @param address Register address
	 * @param data Data
	 */
	void writeConf(const UINT16 &address,const UINT32 &data);

	/**
	 * Wait interrupt VIRQ1 for ever
	 * @param callback Callback to function that will be called when an interrupt occurs
	 * @param time 0 to wait forever, otherwise usec
	 */
	void waitInterrupt(ExternalCallBack callback, const UINT32 &time);

	/**
	 * Read interrupt status
	 * @param status Contains status read
	 */
	void readInterruptStatus(UINT32 *status);

private:
	void initDevice();
	I_VmeAdapter *imp;

};

inline void OptimizedRefined::setVmeAdapter(I_VmeAdapter *handler) {
	imp = handler;
}

#endif  //_OPTIMIZEDREFINED_H