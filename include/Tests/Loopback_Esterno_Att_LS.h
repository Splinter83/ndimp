/*
 * Loopback_Esterno_Att_LS.h
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#ifndef LOOPBACK_ESTERNO_ATT_LS_H_
#define LOOPBACK_ESTERNO_ATT_LS_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_ERROR_LOOPBACK_LS_TEST {
	ERR_LOOP_LS_INT_STATUS_WORD = TEST_CUSTOM_ERR,
	ERR_LOOP_LS_LAST_ACT_WORD,
	ERR_LOOP_LS_ACTION_WORD,
	ERR_LOOP_LS_EFF_DATA_ADDR,
	ERR_LOOP_LS_TABLE_PTR_ADDR,
	ERR_LOOP_LS_PTR_NUM,
	ERR_LOOP_LS_INTERUPT_WORD
};

class Loopback_Esterno_Att_LS: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Loopback_Esterno_Att_LS();
	virtual ~Loopback_Esterno_Att_LS() {
	}
	;

	/*! Executes the test
	 *
	 * the second parameter is the channel (a or b)
	 * the third parameter is 1 if step 1, is 2 if step 2
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 2, ...);
private:
	unsigned short CONTROL_BLOCK_POINTER_WRITE;
	unsigned short PROGRAM_POINTER_WRITE;
	RT_ICW_UNION_TYPE RT_ICW_UNION;
	RT_ICW_UNION_TYPE RT_ICW_UNION2;
	LS_RT_CONTROL_BLOCK_TYPE LS_RT_CONTROL_BLOCK;
	unsigned short SELFTEST_PROCEDURE_MASK_WRITE;
	unsigned short RESTART_LS_WRITE;
	UINT32 INTERFACE_STATUS_WORD_READ;
	HS_CONTROL_BLOCK_TYPE HS_CONTROL_BLOCK;
	HS_DESCRIPTOR_TABLE_TYPE HS_DESCRIPTOR_TABLE;
	SUBADDRESS_CONTROL_WORD_UNION_TYPE SUBADDRESS_CONTROL_WORD_UNION;
	SUBADDRESS_DESCRIPTOR_TYPE SUBADDRESS_DESCRIPTOR;
	HS_MID_CW_DT_UNION_TYPE HS_MID_CW_DT_UNION;
	DATA_POINTER_TYPE HS_DATA_POINTER;
	UINT32 HS_LAST_ACTION_WORD_READ;
	UINT32 HS_ACTION_WORD_READ;
	UINT32 EFFECTIVE_DATA_ADDRESS_READ;
	UINT32 TABLE_POINTER_ADDRESS_READ;
	UINT32 HS_PTR_OFFSET_READ;
	UINT32 INTERRUPT_WORD_1_READ;
};



#endif /* LOOPBACK_ESTERNO_ATT_LS_H_ */
