/*
 * Verifica_Mod_BC.h
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#ifndef VERIFICA_MOD_BC_H_
#define VERIFICA_MOD_BC_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

class Verifica_Mod_BC: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Verifica_Mod_BC();
	virtual ~Verifica_Mod_BC() {
	}
	;

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 0, ...);
private:
	UINT32 ISW_READ;
	UINT32 IAW1_READ;
	UINT32 INSW1_READ;
	UINT32 AW1_READ;
	UINT32 AW2_READ;
};

#endif /* VERIFICA_MOD_BC_H_ */
