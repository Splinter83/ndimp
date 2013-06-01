/*
 * Watch_Dog.h
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#ifndef WATCH_DOG_H_
#define WATCH_DOG_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"
#include "Inizializzazione_LS.h"
#include "Iniz_Tavola_Descr_SA_01_RX.h"
#include "Iniz_Tavola_Descr_SA_01_TX.h"
#include "HS_Selftest.h"

class Watch_Dog: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Watch_Dog();
	virtual ~Watch_Dog();

	/*!Executes the test
	 *
	 * the second parameter is the step (1, 2 or 3)
	 * the third parameter is the terminal address (it must not be passed if the step is 3 and the board is SIMP1 or SIMP2)
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	Inizializzazione_LS iniz_LS;
	Iniz_Tavola_Descr_SA_01_RX iniz_descr_RX;
	Iniz_Tavola_Descr_SA_01_TX iniz_descr_TX;
	HS_Selftest hs_selftest;
	unsigned short RESTART_LS_WRITE;
	UINT32 INTERFACE_CONTROL_WORD_READ;
	unsigned int rt_add;

};

#endif /* WATCH_DOG_H_ */
