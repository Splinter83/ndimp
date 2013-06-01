/*
 * Discrete_Input.h
 *
 *  Created on: 27/11/2012
 *      Author: savino
 */

#ifndef DISCRETE_INPUT_H_
#define DISCRETE_INPUT_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"


enum EN_DISCR_TEST{
	ERR_DISCR_ONE_WALK_CRITICAL = TEST_CUSTOM_ERR,
	ERR_DISCR_ONE_WALK_NOT_CRITICAL,
	ERR_DISCR_ONE_WALK_CRITICAL_DI1_INT,
	ERR_DISCR_ONE_WALK_CRITICAL_DI2_INT,
	ERR_DISCR_ONE_WALK_CRITICAL_DI3_INT,
	ERR_DISCR_ONE_WALK_CRITICAL_DI4_INT,
	ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI5_INT,
	ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI6_INT,
	ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI7_INT,
	ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI8_INT,
	ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI9_INT,
	ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI10_INT,
	ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI11_INT,
	ERR_DISCR_ONE_WALK_NOT_CRITICAL_DI12_INT
};

class Discrete_Input: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Discrete_Input();
	virtual ~Discrete_Input() {
	}
	;

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	UINT32 IDB_READ;
	void printError(UINT32 expected, UINT32 read);

};

#endif /* DISCRETE_INPUT_H_ */
