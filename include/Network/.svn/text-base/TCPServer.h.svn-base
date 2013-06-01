/*
 * TCPServer.h
 *
 *  Created on: 19/giu/2012
 *      Author: emanuele_galli
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "BaseRunnableThread.h"

#include "global_definitions.h"
#include "NetAddress.h"
#include "ConcreteTcpSocket.h"
#include "GenericEventListener.h"
#include "TCPServerEventList.h"


class TCPServer : public BaseRunnableThread,
                  public MultipleNotifier<tBoardNotifableEventList>,
                  public IMultipleListener<tServerListenableEventList>{
public:
	static const int HEADER_SIZE = sizeof(Header);

	/**
	 * Returns TCPServer singleton
	 * @return Singleton pointer to TCP Server
	 */
	static TCPServer* getTcpServer();

	/**
	 * Destructor
	 */
	virtual ~TCPServer();

	/**
	 * Sets network address
	 * @param NetAddress
	 */
	void setNetworkAddress(const NetAddress&);

    void Handle(const CommandResultEvent &event);
    //void Handle(const DiscreteEvent &event);

    void Stop();

protected:
	/**
	 * Mathod called by Start method of BaseRunnableThread.
	 * Starts TCP server (bind, listen and accept)
	 */
    void* run();

    /**
     * Sends a message to client
     * @param id Message ID
     * @param body Message body
     * @param size Body size
     * @return Sent bytes, -1 on error
     */
    int SendMessage(const EN_MSG_IDENTFIER &id, const char* body, const int &size);

private:
	TCPServer();
	static TCPServer* _pTcpServer;
	Header processHeader(const unsigned char*) const;
	void InterpretBuffer(const unsigned char *,const Header &,UINT32);

private:
	NetAddress _netAddr;
	ConcreteTcpSocket _Socket;
	ISocketTcp* _ConnectionSocket;
	bool connected;
	unsigned char* _Buffer;
	unsigned char _Header[HEADER_SIZE];
};

#endif /* TCPSERVER_H_ */
