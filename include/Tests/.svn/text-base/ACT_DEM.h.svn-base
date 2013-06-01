/*
 * ACT_DEM.h
 *
 *  Created on: 12/set/2012
 *      Author: grande
 */

#ifndef ACT_DEM_H_
#define ACT_DEM_H_

#define AVIONIC_ADDR 0x180000
#define ATTACK_ADDR  0x200000

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_ACTDEM_OUT_TEST{
	ERR_ACT = TEST_CUSTOM_ERR,
	ERR_DEM,
	ERR_ACTDEM_FLAG
};

class ACT_DEM : public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	ACT_DEM();
	virtual ~ACT_DEM(){};

	/*!Executes the test
	 *
	 * the second parameter is 1 if step 1, is 2 if step 2, 3 if step 3, 4 if step 4
	 */
	UINT8 execTest(const BoardInterfaceType& i, int num_argomenti = 1, ...);
private:
	UINT32 BC_STATUS_WORD_READ;
	unsigned int ACT;
	unsigned int DEM;
	unsigned int BC_CONTROL_WORD_READ;
	unsigned int HANDOVER_STATUS_WORD_REG;
	unsigned int HANDOVER_CONTROL_WORD_REG;
	unsigned int HANDOVER_MINOR_LOOP_TIMER;
	unsigned int PATTERN;
};



#endif /* ACT_DEM_H_ */
