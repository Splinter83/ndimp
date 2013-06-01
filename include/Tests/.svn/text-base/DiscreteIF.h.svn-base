/*
 * DiscreteIF.h
 *
 *  Created on: 21/nov/2012
 *      Author: galileo
 */

#ifndef DISCRETEIF_H_
#define DISCRETEIF_H_

#include "I_TEST.h"

enum EN_ERROR_DISCRETE_IF_TEST{
	ERR_DISCRETE_IF_STATUS_REG_0 = TEST_CUSTOM_ERR,
	ERR_DISCRETE_IF_CSMUWE_1,
	ERR_DISCRETE_IF_RESET_DISOUT_1,
	ERR_DISCRETE_IF_CSMUWE_0,
	ERR_DISCRETE_IF_RESET_DISOUT_0
};

class Discrete_IF : public I_TEST{
public:
	Discrete_IF();
	virtual ~Discrete_IF();

	/*!Executes the Discrete I/F test for the SIMP family board
	 *
	 */
	UINT8 execTest(const BoardInterfaceType& i, int num_argomenti = 0, ...);
};

#endif /* DISCRETEIF_H_ */
