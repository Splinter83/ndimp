/*
 * IF_Optimized_Bus_Test.h
 *
 *  Created on: 07/set/2012
 *      Author: grande
 */

#ifndef IF_OPTIMIZED_BUS_TEST_H_
#define IF_OPTIMIZED_BUS_TEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"


class IF_Optimized_Bus_Test : public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	IF_Optimized_Bus_Test();
	virtual ~IF_Optimized_Bus_Test(){};

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	unsigned int uno_walking;
	UINT32 uno_walking_read;
	unsigned int pattern_double_word[12];
	UINT32 pattern_double_word_read;
	unsigned int pattern_byte[4];
	UINT32 pattern_byte_read;
	unsigned int pattern_word[4];
	UINT32 pattern_word_read;
	unsigned int pattern_three_byte[4];
	UINT32 pattern_three_byte_read;
};



#endif /* IF_OPTIMIZED_BUS_TEST_H_ */
