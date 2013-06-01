/*
 * InterruptLSTest.h
 *
 *  Created on: 29/nov/2012
 *      Author: galileo
 */

#ifndef INTERRUPTLSTEST_H_
#define INTERRUPTLSTEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

class Interrupt_LS_Test : public I_TEST{
public:
	Interrupt_LS_Test();
	virtual ~Interrupt_LS_Test();

	/*!Executes the Interrupt test. It is executed in 2 steps
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
};

#endif /* INTERRUPTLSTEST_H_ */
