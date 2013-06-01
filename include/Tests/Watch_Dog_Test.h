/*
 * Watch_Dog_Test.h
 *
 *  Created on: 10/set/2012
 *      Author: grande
 */

#ifndef WATCH_DOG_TEST_H_
#define WATCH_DOG_TEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

class Watch_Dog_Test: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Watch_Dog_Test();
	virtual ~Watch_Dog_Test() {
	}
	;

	/*!Executes the test
	 *
	 * the second parameter is the step: if the board is STIMP there are 2 steps, if the board is SIMP there are 3 steps
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	UINT32 readloop;

};

#endif /* WATCH_DOG_TEST_H_ */
