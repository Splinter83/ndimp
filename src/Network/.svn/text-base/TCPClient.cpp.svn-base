/*
 * SimpStimpProject: TCPClient.cpp
 *
 *  Created on: 08/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "TCPClient.h"
#include "ISocketTcp.h"
#include "TCPFactoryMessage.h"
#include "MutextCondition.h"
#include "Logger.h"

#include <string.h>
#include <string>

#include <iostream>

TCPClient::TCPClient() : BaseRunnableThread("TCPClient"),
						 _address((short unsigned) 0),
						 _ConnectionSocket(NULL),
						 _mutexCond(new MutexCondition(new Mutex)){
	_isSocketClosed = false;
}

TCPClient::~TCPClient() {
	if(_ConnectionSocket != NULL)
		if(_ConnectionSocket->IsConnected())
			_ConnectionSocket->Close();
	_isStopped = true;
	_isSocketClosed = true;
	_mutexCond->Signal();
}

bool TCPClient::Connect(){
	/**if(_ConnectionSocket != NULL)
		if(_ConnectionSocket->IsConnected())
			return true;*/

	std::cout << "TCPClient Connecting" << std::endl;
	if(_isSocketClosed)
		_isSocketClosed = !_Socket.CreateSocket();

	if(_isSocketClosed)
		return false;

	_Socket.Connect(_address);
	_ConnectionSocket=&_Socket;

	if(!_Socket.IsConnected())
		return false;
	_mutexCond->Signal();
	Logger::getLogger()->Log(DEBUG_LEVEL,"TCP Client Connected");
	return _ConnectionSocket->IsConnected();


}

void TCPClient::Disconnect(){
	if(_ConnectionSocket != NULL)
		if(_ConnectionSocket->IsConnected())
			_ConnectionSocket->Close();
	_isSocketClosed = true;
	//Stop();
}

void* TCPClient::run(){
	//Wait first Connect command
	bool isConnected = false;
	int recv = 0;
	while(!_isStopped){
		//msg._buffermsg._buffer
		_mutexCond->Wait();
		/*
		std::cout << "TCPClient Connecting" << std::endl;
		isConnected = _Socket.Connect(_address);
		_ConnectionSocket=&_Socket;
		std::cout << "TCPClient Connected" << std::endl;
		 */
		if(_ConnectionSocket != NULL){
			while(!_ConnectionSocket->IsConnected()){
				//While for read
				char buffer[256];
				recv = _ConnectionSocket->Read((unsigned char*)buffer,256);
				if(recv <= 0){
					isConnected = false;
					//_ConnectionSocket->Close();
					//_ConnectionSocket->CreateSocket();
					std::cerr << "TCPClient disconnected" << std::endl;
				}
			}
		}
		//Sleep(500000);
	}
	std::cout << "TCPClient Stopped" << std::endl;
	return NULL;
}

int TCPClient::Send(const LogMsg& msg){
	if(_ConnectionSocket == NULL)
		return -1;
	std::vector<char> message = TCPFactoryMessage::CreateTcpMessage(EN_MSG_LOG,msg._buffer,msg._size);
	char *buffer = new char[message.size() + 1];
	memset(buffer,0,message.size() + 1);
	for(UINT32 i = 0; i < message.size();++i)
		buffer[i] = message[i];
	int bytes = 0;
	if(_ConnectionSocket->IsConnected())
		bytes = _ConnectionSocket->Write((UINT8*)buffer,message.size());
	delete [] buffer;
	return bytes;
}

int TCPClient::Send(const DiscreteMsg& msg){
	std::cout << "TCPClient Send Received" << std::endl;
	if(_ConnectionSocket == NULL)
		return -1;
	std::vector<char> message = TCPFactoryMessage::CreateTcpMessage(EN_MSG_DISCRETE,msg._buffer,msg._size);
	char *buffer = new char[message.size()];
	for(UINT32 i = 0; i < message.size();++i)
		buffer[i] = message[i];
	int bytes = 0;
	if(_ConnectionSocket->IsConnected())
		bytes = _ConnectionSocket->Write((UINT8*)buffer,message.size());
	std::cout << "TCPClient Send Done" << std::endl;
	delete [] buffer;
	return bytes;
}
