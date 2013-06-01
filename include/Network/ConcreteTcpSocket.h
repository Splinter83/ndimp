/*
 * TcpSocket.h
 *
 *  Created on: 20/giu/2012
 *      Author: emanuele_galli
 */

#ifndef CONCRETE_TCPSOCKET_H_
#define CONCRETE_TCPSOCKET_H_

#include "TcpSocketDecorator.h"

class ConcreteTcpSocket : public TcpSocketDecorator{
public:
	ConcreteTcpSocket();
	virtual ~ConcreteTcpSocket();
};

#endif /* CONCRETE_TCPSOCKET_H_ */

