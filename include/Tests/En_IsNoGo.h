/*
 * En_IsNoGo.h
 *
 *  Created on: 27/nov/2012
 *      Author: savino
 */

#ifndef EN_ISNOGO_H_
#define EN_ISNOGO_H_

#define AVIONIC_ADDR 0x180000
#define ATTACK_ADDR  0x200000

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_ISNOGO_OUT_TEST{
	ERR_READ_INOGO = TEST_CUSTOM_ERR,
	ERR_WRITE_INOGO,
	ERR_RESET_INOGO
};

class En_IsNoGo : public I_TEST {
public:

	En_IsNoGo();
	virtual ~En_IsNoGo(){};

	/*!Executes the test
	 *
	 * the second parameter is 1 if step 1, is 2 if step 2, 3 if step 3, 4 if step 4
	 */
	UINT8 execTest(const BoardInterfaceType& i, int num_argomenti = 1, ...);
private:
	UINT32 flagReg;
	unsigned int IS_NOGO_RW_REG;
	unsigned int IS_NOGO_WORD_WRITE_REG;
	unsigned int IS_NOGO_WORD_RESET_REG;
	unsigned int INOGO;
};



#endif /* EN_ISNOGO_H_ */
