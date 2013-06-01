/*
 * Loopback_Esterno.h
 *
 *  Created on: 08/set/2012
 *      Author: grande
 */

#ifndef LOOPBACK_ESTERNO_H_
#define LOOPBACK_ESTERNO_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

/**
 * Custom error for Extern Loopback test
 */
enum EN_ERROR_LOOPBACK_TEST{
	ERR_LOOP_STATUS_WORD = TEST_CUSTOM_ERR,//!< ERR_LOOP_STATUS_WORD
	ERR_LOOP_BIT_WORD,                     //!< ERR_LOOP_BIT_WORD
	ERR_LOOP_INTERRUPT_WORD,               //!< ERR_LOOP_INTERRUPT_WORD
    ERR_LOOP_LAST_ACTION_WORD,             //!< ERR_LOOP_LAST_ACTION_WORD
    ERR_LOOP_PTR_NUM                       //!< ERR_LOOP_PTR_NUM
};

class Loopback_Esterno: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Loopback_Esterno();
	virtual ~Loopback_Esterno() {
	}
	;

	/**
	 *
	 * @param
	 * @param num_argomenti Gets two params: the first is the channel (a or b),
	 * the second one is optional and is used to disable board test (true if disabled)
	 * @return 0 on success, > 0 otherwise
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 2, ...);
private:
	HS_CONTROL_BLOCK_TYPE HS_CONTROL_BLOCK;
	HS_MID_CW_DT_UNION_TYPE HS_MID_CW_DT_UNION;
	RESTART_HS_TYPE RESTART_HS;
	UINT32 HS_STATUS_WORD_READ;
	UINT32 HS_BIT_WORD_READ;
	UINT32 INTERRUPT_WORD_1_READ;
	UINT32 HS_LAST_ACTION_WORD_READ;
	UINT32 HS_PTR_OFFSET_READ;
};



#endif /* LOOPBACK_ESTERNO_H_ */
