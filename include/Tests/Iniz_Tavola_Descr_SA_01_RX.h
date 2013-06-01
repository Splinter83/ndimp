/*
 * Iniz_Tavola_Descr_SA_01_RX.h
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#ifndef INIZ_TAVOLA_DESCR_SA_01_RX_H_
#define INIZ_TAVOLA_DESCR_SA_01_RX_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

class Iniz_Tavola_Descr_SA_01_RX : public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Iniz_Tavola_Descr_SA_01_RX();
	virtual ~Iniz_Tavola_Descr_SA_01_RX(){};

	/*!Executes the test
	 *
	 * the parameter RCI must be passed as second parameter, and this must be set to 1 if the interrupt test must be executed (else 0)
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	SUBADDRESS_CONTROL_WORD_UNION_TYPE SUBADDRESS_CONTROL_WORD_UNION;
	SUBADDRESS_DESCRIPTOR_TYPE SUBADDRESS_DESCRIPTOR;
	LS_RT_CONTROL_BLOCK_TYPE LS_RT_CONTROL_BLOCK;
	int RCI;

};



#endif /* INIZ_TAVOLA_DESCR_SA_01_RX_H_ */
