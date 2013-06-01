/*
 * Parity_Test.h
 *
 *  Created on: 08/set/2012
 *      Author: grande
 */

#ifndef PARITY_TEST_H_
#define PARITY_TEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_RT_PARITY_TEST{
	ERR_PAR_STATUS_WORD_PARITY_ERROR = TEST_CUSTOM_ERR,
	ERR_PAR_BITE_WORD_PARITY_ERROR ,
	ERR_PAR_STATUS_WORD,
	ERR_PAR_BITE_WORD
};

class Parity_Test : public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Parity_Test();
	virtual ~Parity_Test(){};

	/*!Executes the test
	 *
	 * the second parameter is 1 if step 1, is 2 if step 2
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	unsigned short CONTROL_BLOCK_POINTER_WRITE;
	unsigned short PROGRAM_POINTER_WRITE;
	unsigned short RESTART_LS_WRITE;
	UINT32 INTERFACE_STATUS_WORD_READ;
	UINT32 LS_RT_ERROR_BITE_WORD_READ;

};



#endif /* PARITY_TEST_H_ */
