/*
 * Address_Test.h
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#ifndef ADDRESS_TEST_H_
#define ADDRESS_TEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_ERROR_RT_ADDRESS_TEST{
	ERR_RT_ADDR_VAL = TEST_CUSTOM_ERR,
	ERR_RT_ADDR_PARITY
};

class Address_Test: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Address_Test();
	virtual ~Address_Test() {
	}
	;

	/**
	 * Executes the uno-walking RT address test (parity bit included)
	 * @param bt Board Interface configuration ID
	 * @param num_argomenti No extra arguments
	 * @return 0 if ok, 2 otherwise
	 */
	UINT8 execTest(const BoardInterfaceType& bt, int num_argomenti = 0, ...);
private:
	unsigned short RESTART_LS_WRITE;
	UINT32 INTERFACE_CONTROL_WORD_READ;
	unsigned int rt_add;

};

#endif /* ADDRESS_TEST_H_ */
