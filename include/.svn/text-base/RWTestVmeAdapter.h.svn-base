/*
 * RWTestVmeAdapter.h
 *
 *  Created on: 11/giu/2012
 *      Author: emanuele_galli
 */

#ifndef RWTESTVMEADAPTER_H_
#define RWTESTVMEADAPTER_H_

#include "I_VmeAdapter.h"

/*!
 * \class RW_TestVmeAdapter
 * Implements I_VmeAdapter. This class should be used only for DEBUG purpose. It does not write on VME
 */
class RW_TestVmeAdapter: public I_VmeAdapter{
public:
	/*!
	 * Constructor
	 */
	RW_TestVmeAdapter();

	/*!
	 * Desctructor
	 */
	virtual ~RW_TestVmeAdapter();

	/*!
	 * Initializes VME board
	 */
	void initBoard() throw(std::string);

	/**
	 * Read on a register of FPGA optimized bus controller
	 * @param regAddr Register Address
	 * @return Read value
	 * @throw An exception on error with a string containing error information
	 */
	UINT32 readRegister(UINT32 regAddr) throw(std::string);

	/**
	 * Write on a register of FPGA optimized bus controller
	 * @param regAddr Register Address
	 * @param val Value to be written
	 * @throw An exception on error with a string containing error information
	 */
	void writeRegister(UINT32 regAddr, UINT32 val) throw(std::string);

	void readInterruptStatus(UINT32* status) throw(std::string);

	void waitInterrupt(const UINT32 &time) throw(int);


	/*!
	 * Closes VME board
	 */
	void closeDevice();

	void write8(UINT32 regAddress, UINT8 value) throw(std::string);
	void write16(UINT32 regAddress, UINT16 value) throw(std::string);
	void write24(UINT32 regAddress, UINT32 value) throw(std::string);
	void write32(UINT32 regAddr, UINT32 val) throw(std::string);
	UINT8 read8(UINT32 regAddr32) throw(std::string);
	UINT16 read16(UINT32 regAddr32) throw(std::string);
	UINT32 read24(UINT32 regAddr32) throw(std::string);
	UINT32 read32(UINT32 regAddr32) throw(std::string);

};

#endif /* RWTESTVMEADAPTER_H_ */
