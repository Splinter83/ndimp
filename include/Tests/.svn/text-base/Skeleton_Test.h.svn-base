/*
 * Skeleton_Test.h
 *
 *  Created on: 09/set/2012
 *      Author: grande
 */

#ifndef SKELETON_TEST_H_
#define SKELETON_TEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

class Skeleton_Test: public I_TEST {
public:
	//Test1(VmeAbstractionDevice<int> *device) : I_TEST(device){}
	Skeleton_Test();
	virtual ~Skeleton_Test() {
	}
	;

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 1, ...);
private:
	unsigned int SKELETON_ADDRESS;
	unsigned int pattern_word[7];
	UINT32 pattern_word_read;
};

#endif /* SKELETON_TEST_H_ */
