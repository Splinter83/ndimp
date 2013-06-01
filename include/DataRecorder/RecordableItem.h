/*
 * RecordableItem.h
 *
 *  Created on: 05/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef RECORDABLEITEM_H_
#define RECORDABLEITEM_H_

#include "IRecordable.h"

#include "global_definitions.h"

/*!
 * \class RecordableItem
 * Implements IRecordable interface
 */
class RecordableItem: public IRecordable {
public:
	/*!
	 * RecordableItem constructor
	 * @param MaxBufferSize Maximum buffer size
	 */
	RecordableItem(int MaxBufferSize = MAX_BUF_SIZE);

	/*!
	 * Destructor
	 */
	virtual ~RecordableItem();

	/*!
	 * Reads data and put them into  buffer argument
	 * @param buffer Buffer is refilled with read data
	 * @param size Buffer size
	 * @return
	 */
	int Read(char* buffer, int size);

	/*!
	 * Sets local buffer
	 * @param bufferIn Buffer to copy into local variable
	 * @param sizeIn Buffer size
	 * @return Minimum between local buffer size and sizeIn argument
	 */
	int SetBuffer(const char * bufferIn, int sizeIn);

private:
	int _availableDataSize; ///< Available data size
	char *_plocalBuffer; ///< Local buffer
	int _localBufferSize; ///<   Local buffer size

};

#endif /* RECORDABLEITEM_H_ */
