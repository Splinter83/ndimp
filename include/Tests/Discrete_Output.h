/*
 * Discrete_Output.h
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#ifndef DISCRETE_OUTPUT_H_
#define DISCRETE_OUTPUT_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_DISCR_OUT_TEST{
	ERR_DISCR_OUT_ONE_WALK_CRITICAL = TEST_CUSTOM_ERR,
	ERR_DISCR_OUT_ONE_WALK_NOT_CRITICAL_AFTER,
	ERR_DISCR_OUT_ONE_WALK_NOT_CRITICAL_BEFORE
};

class Discrete_Output: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Discrete_Output();
	virtual ~Discrete_Output() {
	}
	;

	/*!Executes the test
	 *
	 * the second parameter is 1 if step 1, is 2 if step 2
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	UINT32 IDB_READ;
	void printError(UINT32 expected, UINT32 read);

};

#endif /* DISCRETE_OUTPUT_H_ */
