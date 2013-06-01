/*
 * TcpSocket.cpp
 *
 *  Created on: 20/giu/2012
 *      Author: emanuele_galli
 */

#include "TcpSocketDecorator.h"

TcpSocketDecorator::TcpSocketDecorator(ISocketTcp* socket) {
	// TODO Auto-generated constructor stub
	pSocketTcp = socket;
}

TcpSocketDecorator::~TcpSocketDecorator() {
	// TODO Auto-generated destructor stub
}

ISocketTcp* TcpSocketDecorator::Accept(){
	return pSocketTcp->Accept();
}

bool TcpSocketDecorator::Bind(NetAddress address){
	return pSocketTcp->Bind(address);
}

void TcpSocketDecorator::Close(){
	pSocketTcp->Close();
}

bool TcpSocketDecorator::Connect(const NetAddress & address){
	return pSocketTcp->Connect(address);
}

bool TcpSocketDecorator::IsConnected() const{
	return pSocketTcp->IsConnected();
}

int TcpSocketDecorator::Read(unsigned char* buffer, unsigned int size){
	return pSocketTcp->Read(buffer,size);
}

int TcpSocketDecorator::Write(const unsigned char *buffer, unsigned int size){
	return pSocketTcp->Write(buffer,size);
}

bool TcpSocketDecorator::Listen(){
	return pSocketTcp->Listen();
}

bool TcpSocketDecorator::CreateSocket(){
	return pSocketTcp->CreateSocket();
}

