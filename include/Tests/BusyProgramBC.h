/*
 * BusyProgramBC.h
 *
 *  Created on: 07/dic/2012
 *      Author: galileo
 */

#ifndef BUSYPROGRAMBC_H_
#define BUSYPROGRAMBC_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_BC_PROGRAM_BUSY_ERROR{
	ERR_BC_BUSY_IAW = TEST_CUSTOM_ERR,
	ERR_BC_BUSY_ISW,
	ERR_AUX_BUSY_WORD_A,
	ERR_AUX_BUSY_WORD_B
};

class Busy_Program_BC : public I_TEST {
public:
	Busy_Program_BC();
	virtual ~Busy_Program_BC();
	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	unsigned short CONTROL_BLOCK_POINTER_WRITE;
	unsigned short PROGRAM_POINTER_WRITE;
	BC_ICW_UNION_TYPE BC_ICW_UNION;
	LS_BC_CONTROL_BLOCK_TYPE LS_BC_CONTROL_BLOCK;
	DATA_POINTER_TYPE DATA_POINTER;
	unsigned short RESTART_LS_WRITE;
};

#endif /* BUSYPROGRAMBC_H_ */
