/*
 * ModNogo.h
 *
 *  Created on: 27/nov/2012
 *      Author: galileo
 */

#ifndef MODNOGO_H_
#define MODNOGO_H_

#define AVIONIC_ADDR 0x180000
#define ATTACK_ADDR  0x200000

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_MOD_NOGO_OUT_TEST{
	ERR_READ_MOD = TEST_CUSTOM_ERR,
	ERR_WRITE_MOD,
	ERR_RESET_MOD
};

class Mod_Nogo : public I_TEST {
public:
	Mod_Nogo();
	virtual ~Mod_Nogo(){};
	UINT8 execTest(const BoardInterfaceType& i, int num_argomenti = 1, ...);
private:
	UINT32 flagReg;
	unsigned int MOD_NOGO_WORD_READ_REG;
	unsigned int MOD_NOGO_WORD_WRITE_REG;
	unsigned int MOD_NOGO_WORD_RESET_REG;
	unsigned int MNOGO;
};

#endif /* MODNOGO_H_ */
