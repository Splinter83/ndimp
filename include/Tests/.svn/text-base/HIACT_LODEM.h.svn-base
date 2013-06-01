/*
 * HIACT_LODEM.h
 *
 *  Created on: 12/set/2012
 *      Author: grande, savino (27/11/12)
 */

#ifndef HIACT_LODEM_H_
#define HIACT_LODEM_H_

#define DEF_AND_HIA 0x200
#define DEF_AND_LOA 0x400
#define DEF_AND_IP 0xC000

#define AVIONIC_ADDR 0x180000
#define ATTACK_ADDR  0x200000



#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_HIACT_LODEM_OUT_TEST{
	ERR_HIACT_LODEM_HIA = TEST_CUSTOM_ERR,
	ERR_HIACT_LODEM_LOA,
	ERR_ACT_HL,
	ERR_DEM_HL,
	ERR_TIME_OUT
};

class HIACT_LODEM : public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	HIACT_LODEM();
	virtual ~HIACT_LODEM(){};

	/*!Executes the test
	 *
	 * the second parameter is 1 if step 1, is 2 if step 2, 3 if step 3
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	UINT32 BC_STATUS_WORD_READ;
	UINT32 BC_STATUS_INTERRUPT_REG;
	unsigned int HIA;
	unsigned int LOA;
	unsigned int IP;
	unsigned int BC_CONTROL_WORD_READ;
	unsigned int INT_HIACT;
	unsigned int INT_LODEM;
	unsigned int ACT;
	unsigned int DEM;
	unsigned int HANDOVER_STATUS_WORD_REG;
	unsigned int HANDOVER_CONTROL_WORD_REG;
	unsigned int HANDOVER_MINOR_LOOP_TIMER;

};



#endif /* HIACT_LODEM_H_ */
