//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : STIMP.h
//  @ Date : 08/06/2012
//  Author: Emanuele Galli
//
//


#if !defined(_STIMP_H)
#define _STIMP_H

#include "TSAP.h"

/*!
 * \class STIMP
 * STIMP controller
 * Derives from TSAP class
 */
class STIMPboard : public TSAP {
public:

	/*!
	 * Default Constructor. Sets SGA with sga parameters, default base address and RAM size
	 * @param sga
	 */
	STIMPboard(VmeAbstractionDevice *adapter, EN_SGA_ADDRESS sga = EN_SGA_2);

	virtual ~STIMPboard(){};

	//unsigned int read(unsigned int address);
	//void write(unsigned int data, unsigned int address);
	UINT32 execTest(const TestStruct& test);
	void initBoard();

	/**
	 * Reads all discrete status
	 * @return Returns a vector
	 */
	AllDiscreteType readAllDiscrete();
private:
	void initSTIMPBoard();
};

#endif  //_STIMP_H
