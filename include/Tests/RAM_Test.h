/*
 * RAM_Test.h
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#ifndef RAM_TEST_H_
#define RAM_TEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_RAM_TEST{
	ERR_RAM_COMPL = TEST_CUSTOM_ERR,
	ERR_RAM_TOGGLE
};

class RAM_Test: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	RAM_Test();
	virtual ~RAM_Test() {
	}
	;

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 0, ...);
private:
	UINT32 word_read;

};

#endif /* RAM_TEST_H_ */
