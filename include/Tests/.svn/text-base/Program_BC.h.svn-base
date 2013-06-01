/*
 * Program_BC.h
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#ifndef PROGRAM_BC_H_
#define PROGRAM_BC_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_BC_PROGRAM_ERROR{
	ERR_BC_IAW = TEST_CUSTOM_ERR,
	ERR_BC_ISW,
	ERR_AUX_WORD_A,
	ERR_AUX_WORD_B
};

class Program_BC: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Program_BC();
	virtual ~Program_BC() {
	}
	;

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

#endif /* PROGRAM_BC_H_ */
