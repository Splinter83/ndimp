/*
 * HS_Interrupt_Pointer_Offset.h
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#ifndef HS_INTERRUPT_POINTER_OFFSET_H_
#define HS_INTERRUPT_POINTER_OFFSET_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_ERROR_HS_POINTER_OFFSET{
	ERR_LAST_ACTION_WORD = TEST_CUSTOM_ERR,
	ERR_PNTR_NUM,
	ERR_PNTR_NUM_COUNTER,
	ERR_PNTR_NUM_END_LOOP
};

class HS_Interrupt_Pointer_Offset: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	HS_Interrupt_Pointer_Offset();
	virtual ~HS_Interrupt_Pointer_Offset() {
	}
	;

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 0, ...);
private:
	HS_CONTROL_BLOCK_TYPE HS_CONTROL_BLOCK;
	HS_MID_CW_DT_UNION_TYPE HS_MID_CW_DT_UNION;
	HS_BITE_BUFFER_TYPE HS_BITE_BUFFER;
	RESTART_HS_TYPE RESTART_HS;
	UINT32 HS_LAST_ACTION_WORD_READ;
	UINT32 HS_PTR_OFFSET_READ;
};

#endif /* HS_INTERRUPT_POINTER_OFFSET_H_ */
