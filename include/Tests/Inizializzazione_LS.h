/*
 * Inizializzazione_LS.h
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#ifndef INIZIALIZZAZIONE_LS_H_
#define INIZIALIZZAZIONE_LS_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

class Inizializzazione_LS : public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Inizializzazione_LS();
	virtual ~Inizializzazione_LS(){};

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 0, ...);
private:
	unsigned short CONTROL_BLOCK_POINTER_WRITE;
	unsigned short PROGRAM_POINTER_WRITE;
	RT_ICW_UNION_TYPE RT_ICW_UNION;
	LS_RT_CONTROL_BLOCK_TYPE LS_RT_CONTROL_BLOCK;
};



#endif /* INIZIALIZZAZIONE_LS_H_ */
