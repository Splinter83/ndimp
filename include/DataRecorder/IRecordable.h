/*
 * IRecordable.h
 *
 *  Created on: 05/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef IRECORDABLE_H_
#define IRECORDABLE_H_


/*!
 * \interface IRecordable interface
 */
class IRecordable {
public:
	IRecordable();
	virtual ~IRecordable();

	/*!
	 * Inserts read data into buffer
	 * @param buffer Pointer to buffer
	 * @param size Buffer size
	 * @return Size of read data
	 */
	virtual int Read(char * buffer, int size) = 0;
};

#endif /* IRECORDABLE_H_ */
