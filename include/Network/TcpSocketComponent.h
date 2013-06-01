/*
 * TcpSocketComponent.h
 *
 *  Created on: 20/giu/2012
 *      Author: emanuele_galli
 */

#ifndef TCPSOCKETCOMPONENT_H_
#define TCPSOCKETCOMPONENT_H_

#include "ISocketTcp.h"


class TcpSocketComponent : public ISocketTcp {
public:
	TcpSocketComponent();
	TcpSocketComponent(int fd, const NetAddress&);
	virtual ~TcpSocketComponent();

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
	int _Socket;
	NetAddress _EndPoint;
	bool _HasBind;
	bool _IsConnected;
};

inline bool TcpSocketComponent::IsConnected() const{
	return _IsConnected;
}

#endif /* TCPSOCKETCOMPONENT_H_ */
