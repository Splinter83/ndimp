/*
 * XmlLogDevice.h
 *
 *  Created on: 06/set/2012
 *  Author: Emanuele Galli
 *
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef XMLLOGDEVICE_H_
#define XMLLOGDEVICE_H_

#include "IRecordingDevice.h"
#include "Log.hxx"
#include "NetAddress.h"
#include "ConcreteTcpSocket.h"

/**
 * @class XmlLogDevice
 * Device who writes an XML message complaint to Log.xsd and sends on a TCP socket
 */
class XmlLogDevice : public IRecordingDevice {
public:
	XmlLogDevice();

	/*!
	 * Constructor
	 * @param address Network address of server
	 */
	XmlLogDevice(const NetAddress& address);

	/*!
	 * Destructor
	 */
	virtual ~XmlLogDevice();

	/*!
	 * Close TCP-client connection
	 */
    void Close();

    /*!
     * Open TCP-client Connection
     * @return True if connected, false otherwise
     */
    bool Open();

    /*!
     * Write a string on Ethernet using format described in Log.xsd
     * @param buffer String to write
     * @param size String size
     * @return Buffer size written on stdout
     */
    int Write(const char * buffer, int size);

private:
    xml_schema::namespace_infomap _map;
};

#endif /* XMLLOGDEVICE_H_ */
