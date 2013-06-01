/*
 * TcpSocket.h
 *
 *  Created on: 20/giu/2012
 *      Author: emanuele_galli
 */

#ifndef TCPSOCKET_DECORATOR_H_
#define TCPSOCKET_DECORATOR_H_

#include "ISocketTcp.h"

/**
 * @class TcpSocketDecorator
 * Decorator of a TcpSocket.
 * This class could be inherited to extend behavior to an ISocketTcp component
 */

class TcpSocketDecorator : public ISocketTcp{
public:
	TcpSocketDecorator(ISocketTcp* );
	virtual ~TcpSocketDecorator();

	ISocketTcp* Accept();
	bool Bind(NetAddress);
	void Close();
	bool Connect(const NetAddress & address);
	bool IsConnected() const;
	int Read(unsigned char* buffer, unsigned int size);
	int Write(const unsigned char *buffer, unsigned int size);
	bool Listen();
	bool CreateSocket();

private:
	ISocketTcp *pSocketTcp;
};

#endif /* TCPSOCKET_DECORATOR_H_ */
