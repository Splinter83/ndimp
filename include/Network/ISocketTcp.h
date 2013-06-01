/*
 * ISocket.h
 *
 *  Created on: 20/giu/2012
 *      Author: emanuele_galli
 */

#ifndef ISOCKETTCP_H_
#define ISOCKETTCP_H_

#include "NetAddress.h"

/**
 * @interface ISocketTcp
 */
class ISocketTcp {
public:
	ISocketTcp();
	virtual ~ISocketTcp();
	/**
	 * Accept a new connection
	 * @return The socket with a client on success, NULL otherwise
	 */
	virtual ISocketTcp* Accept() = 0;

	/**
	 * Bind a socket to an address
	 * @param add Network addres
	 * @return True on success, false otherwise
	 */
	virtual bool Bind(NetAddress add) = 0;

	/**
	 * Close the current socket
	 */
	virtual void Close() = 0;

	/**
	 * Connects to a server. It is a blocking call
	 * @param address Server address
	 * @return True on success, false otherwise
	 */
	virtual bool Connect(const NetAddress & address) = 0;

	/**
	 * Returns connection status
	 * @return True if connected, false otherwise
	 */
	virtual bool IsConnected() const = 0;

	/**
	 * Reads a message on the socket. It is a blocking call
	 * @param buffer read characters
	 * @param size Size of read message
	 * @return Read character
	 */
	virtual int Read(unsigned char* buffer, unsigned int size) = 0;

	/**
	 * Writes a message on the socket. It is a blocking call
	 * @param buffer Message to send
	 * @param size of message
	 * @return Written character
	 */
	virtual int Write(const unsigned char *buffer, unsigned int size) = 0;

	/**
	 *  Allows the process to listen on the socket for connections
	 * @return True on success, false otherwise
	 */
	virtual bool Listen() = 0;

	/**
	 * Create a new socket
	 * @return True on success, false otherwise
	 */
	virtual bool CreateSocket() = 0;
};

#endif /* ISOCKETTCP_H_ */
