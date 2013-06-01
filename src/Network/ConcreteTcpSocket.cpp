/*
 * TcpSocket.cpp
 *
 *  Created on: 20/giu/2012
 *      Author: emanuele_galli
 */

#include "ConcreteTcpSocket.h"
#include "TcpSocketComponent.h"

ConcreteTcpSocket::ConcreteTcpSocket() : TcpSocketDecorator(new TcpSocketComponent()){
	// TODO Auto-generated constructor stub

}

ConcreteTcpSocket::~ConcreteTcpSocket() {
	// TODO Auto-generated destructor stub
}

