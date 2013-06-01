/*
 * BitHistoryTest.h
 *
 *  Created on: 19/nov/2012
 *      Author: grande
 */

#ifndef BITHISTORYTEST_H_
#define BITHISTORYTEST_H_

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_HISTORY_TEST{
	ERR_HIS_COMPL = TEST_CUSTOM_ERR,
	ERR_HIS_TOGGLE,
	ERR_HIS_ONE_WALK
};

class BitHistory_Test : public I_TEST{
public:
	BitHistory_Test();
	virtual ~BitHistory_Test();

	/*!Executes the test
	 *
	 */
	UINT8 execTest(const BoardInterfaceType&, int num_argomenti = 0, ...);
private:
	UINT32 word_read;
};

#endif /* BITHISTORYTEST_H_ */
