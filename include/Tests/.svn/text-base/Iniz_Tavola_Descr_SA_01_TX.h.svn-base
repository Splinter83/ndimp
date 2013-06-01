/*
 * Iniz_Tavola_Descr_SA_01_TX.h
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#ifndef INIZ_TAVOLA_DESCR_SA_01_TX_H_
#define INIZ_TAVOLA_DESCR_SA_01_TX_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

class Iniz_Tavola_Descr_SA_01_TX : public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Iniz_Tavola_Descr_SA_01_TX();
	virtual ~Iniz_Tavola_Descr_SA_01_TX(){};

	/*!Executes the test
	 *
	 * the parameter RCI must be passed as second parameter, and this must be set to 1 if the interrupt test must be executed (else 0)
	 * the third parameter is the terminal address
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 2, ...);
private:
	SUBADDRESS_CONTROL_WORD_UNION_TYPE SUBADDRESS_CONTROL_WORD_UNION;
	SUBADDRESS_DESCRIPTOR_TYPE SUBADDRESS_DESCRIPTOR;
	LS_RT_CONTROL_BLOCK_TYPE LS_RT_CONTROL_BLOCK;
	int RCI;
	unsigned short RESTART_LS_WRITE;
	UINT32 INTERFACE_CONTROL_WORD_READ;
	unsigned int rt_add;
	unsigned short CONTROL_BLOCK_POINTER_WRITE;
};



#endif /* INIZ_TAVOLA_DESCR_SA_01_TX_H_ */
