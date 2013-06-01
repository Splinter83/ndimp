/*
 * ConsoleDevice.h
 *
 *  Created on: 06/giu/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef CONSOLEDEVICE_H_
#define CONSOLEDEVICE_H_

#include "IRecordingDevice.h"

/*!
 * \class ConsoleDevice
 * Device who writes on standard output
 */
class ConsoleDevice : public IRecordingDevice {
public:
	/*!
	 * Constructor
	 */
	ConsoleDevice();

	/*!
	 * Destructor
	 */
	virtual ~ConsoleDevice();

	/*!
	 * Not Used
	 */
    void Close();

    /*!
     * Not Used
     */
    bool Open();

    /*!
     * Write a string on console standard output
     * @param buffer String to write
     * @param size String size
     * @return Buffer size written on stdout
     */
    int Write(const char * buffer, int size);
};

#endif /* CONSOLEDEVICE_H_ */
