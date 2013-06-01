/*
 * Nmi_3909.h
 *
 *  Created on: 28/nov/2012
 *      Author: savino
 */

#ifndef NMI_3909_H_
#define NMI_3909_H_

#define AVIONIC_ADDR 0x180000
#define ATTACK_ADDR  0x200000

#include "I_TEST.h"
#include "VmeAbstractionDevice.h"
#include "memoria.h"

enum EN_NMI_3909_OUT_TEST{
	ERR_READ_NMI = TEST_CUSTOM_ERR,
	ERR_WRITE_NMI,
	ERR_RESET_NMI
};

class Nmi_3909 : public I_TEST {
public:
	Nmi_3909();
	virtual ~Nmi_3909();
	UINT8 execTest(const BoardInterfaceType& i, int num_argomenti = 1, ...);
private:
	UINT32 flagReg;
	unsigned int NMI_WORD_READ_REG;
	unsigned int NMI_WORD_WRITE_REG;
	unsigned int NMI_WORD_RESET_REG;
	unsigned int NMI;
};

#endif /* NMI_3909_H_ */
