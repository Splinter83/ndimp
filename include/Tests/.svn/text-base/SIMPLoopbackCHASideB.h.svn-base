/*
 * SIMPLoopbackCHASideB.h
 *
 *  Created on: 22/nov/2012
 *      Author: galileo
 */

#ifndef SIMPLOOPBACKCHASIDEB_H_
#define SIMPLOOPBACKCHASIDEB_H_

#include "I_TEST.h"
#include "memoria.h"

class SIMP_Loopback_CH_A_Side_B : public I_TEST {
public:
	SIMP_Loopback_CH_A_Side_B();
	virtual ~SIMP_Loopback_CH_A_Side_B();

	/**
	 * Executes External loopback for the board SIMP in case of channel A side B
	 * @param BoardInterfaceType Current board interface
	 * @param num_argomenti 1 argument that is the number of steps
	 * @return TEST_OK and NEXT_STEP on success, others error on failure
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);

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

#endif /* SIMPLOOPBACKCHASIDEB_H_ */
