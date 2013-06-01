/*
 * HS_Selftest.h
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#ifndef HS_SELFTEST_H_
#define HS_SELFTEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_ERROR_HS_SELFTEST{
	ERR_HS_STATUS_WORD = TEST_CUSTOM_ERR,
	ERR_HS_LAST_ACTION_WORD,
	ERR_HS_BIT_WORD,
	ERR_HS_PNTR_NUM,
	ERR_HS_INTERRUPT_WORD,
	ERR_HS_DATA_RX
};

class HS_Selftest: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	HS_Selftest();
	virtual ~HS_Selftest() {
	}
	;

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 0, ...);
private:
	HS_CONTROL_BLOCK_TYPE HS_CONTROL_BLOCK;
	HS_BITE_BUFFER_TYPE HS_BITE_BUFFER;
	HS_MID_CW_ST_UNION_TYPE HS_MID_CW_ST_UNION;
	RESTART_HS_TYPE RESTART_HS;
	UINT32 HS_STATUS_WORD_READ;
	UINT32 HS_LAST_ACTION_WORD_READ;
	UINT32 HS_BIT_WORD_READ;
	UINT32 HS_PTR_OFFSET_READ;
	UINT32 INTERRUPT_WORD_1_READ;
};



#endif /* HS_SELFTEST_H_ */
