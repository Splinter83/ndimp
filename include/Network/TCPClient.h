/*
 * SimpStimpProject: TCPClient.h
 *
 *  Created on: 08/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include "Singleton.h"
#include "TCPClient.h"
#include "BaseRunnableThread.h"
#include "NetAddress.h"
#include "ConcreteTcpSocket.h"
#include "TsapMessage.h"
#include "GenericEventListener.h"


class ISocketTcp;
class MutexCondition;

class TCPClient :
		public Singleton<TCPClient, CreateThreadSafe>,
		public BaseRunnableThread{

	SINGLETON_THREAD_SAFE

public:
	virtual ~TCPClient();

	/**
	 *
	 * @param msg
	 */
	int Send(const LogMsg& msg);

	/**
	 *
	 * @param msg
	 */
	int Send(const DiscreteMsg& msg);

	bool Connect();

	void Disconnect();

	void SetNetAddress(const NetAddress& address);

	bool IsConnected() const;

private:
	TCPClient();
	void* run();

private:
    ISocketTcp* _ConnectionSocket;
    ConcreteTcpSocket _Socket;
    NetAddress _address;
    MutexCondition *_mutexCond;
    bool _isSocketClosed;
};

inline void TCPClient::SetNetAddress(const NetAddress& address){
	_address = address;
}

inline bool TCPClient::IsConnected() const{
	if(_ConnectionSocket)
		return _ConnectionSocket->IsConnected();
	return false;
}

#endif /* TCPCLIENT_H_ */
