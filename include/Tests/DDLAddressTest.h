/*
 * DDLAddressTest.h
 *
 *  Created on: 26/nov/2012
 *      Author: galileo
 */

#ifndef DDLADDRESSTEST_H_
#define DDLADDRESSTEST_H_

#include "VmeAbstractionDevice.h"
#include "memoria.h"
#include "I_TEST.h"

class DDL_Address_Test : public I_TEST {
public:
	DDL_Address_Test();
	virtual ~DDL_Address_Test();

	/**
	 * Verifies that DDL RT address on SIMP board is equal to 0 (RT = 1)
	 * @param bt Board Interface configuration ID
	 * @param num_argomenti No extra arguments
	 * @return 0 if ok, 2 otherwise
	 */
	UINT8 execTest(const BoardInterfaceType& bt, int num_argomenti = 0, ...);

private:
	unsigned short RESTART_LS_WRITE;
	UINT32 INTERFACE_CONTROL_WORD_READ;
};

#endif /* DDLADDRESSTEST_H_ */
