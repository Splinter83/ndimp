/*
 * Verifica_Progr_BC.h
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#ifndef VERIFICA_PROGR_BC_H_
#define VERIFICA_PROGR_BC_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

class Verifica_Progr_BC: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Verifica_Progr_BC();
	virtual ~Verifica_Progr_BC() {
	}
	;

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 0, ...);
private:
	unsigned short PROGRAM_POINTER_WRITE;
	unsigned short RESTART_LS_WRITE;
};

#endif /* VERIFICA_PROGR_BC_H_ */
