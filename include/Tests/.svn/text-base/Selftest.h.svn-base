/*
 * Selftest.h
 *
 *  Created on: 08/set/2012
 *      Author: grande
 */

#ifndef SELFTEST_H_
#define SELFTEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

class Selftest: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Selftest();
	virtual ~Selftest() {
	}
	;

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 0, ...);
private:
	unsigned short CONTROL_BLOCK_POINTER_WRITE;
	unsigned short PROGRAM_POINTER_WRITE;
	RT_ICW_UNION_TYPE RT_ICW_UNION;
	unsigned short SELFTEST_PROCEDURE_MASK_WRITE;
	unsigned short RESTART_LS_WRITE;
	UINT32 INTERFACE_STATUS_WORD_READ;
	UINT32 LS_RT_ERROR_BITE_WORD_READ;
	UINT32 LS_RT_RAM_BLOCK_INDEX_READ;
};

#endif /* SELFTEST_H_ */
