/*
 * TcpSocketComponent.cpp
 *
 *  Created on: 20/giu/2012
 *      Author: emanuele_galli
 */

#include "TcpSocketComponent.h"
#include <netdb.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG
#endif

#ifdef DEBUG
	#include <iostream>
#endif

TcpSocketComponent::TcpSocketComponent() {
	// TODO Auto-generated constructor stub
	CreateSocket();
}

TcpSocketComponent::TcpSocketComponent(int fd, const NetAddress& addr) : _Socket(fd), _EndPoint(addr){
    int optval = 1;
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof (optval));
    setsockopt(_Socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof (timeout));
    //setsockopt(_Socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof (timeout));
    _IsConnected = true;
}

TcpSocketComponent::~TcpSocketComponent() {
	// TODO Auto-generated destructor stub
}

ISocketTcp* TcpSocketComponent::Accept(){
    sockaddr_in addr;
    socklen_t   len=sizeof(sockaddr_in);

    if(!_IsConnected)
    	return NULL;

    //Accept di una nuova connessioni in arrivo
    int child_socket=accept(_Socket,(sockaddr *)&addr,&len);

    if (child_socket == 0)
      return NULL;
    else
    {
      unsigned int   address=ntohl(addr.sin_addr.s_addr);
      //printf("addr:%x,%x,%s\n",address,addr.sin_addr.s_addr,inet_ntoa(addr.sin_addr));
      unsigned short port=ntohs(addr.sin_port);

      unsigned char address_bytes[4];

      for (int i=0; i<4; i++)
      {
        address_bytes[3-i]=(unsigned)(address & ((unsigned)0xff));
        address = (address >> 8L);
      }
      NetAddress inet_address(address_bytes,port);
      return new TcpSocketComponent(child_socket,inet_address);
    }
}

bool TcpSocketComponent::Bind(NetAddress address){
	if(_Socket <= 0)
		return false;

    sockaddr_in addr;
    memset((char *)&addr,0,sizeof(sockaddr_in));
    addr.sin_family=AF_INET;
    unsigned long my_addr=0;
    for (int i=0; i<4; i++){
      my_addr=(my_addr<<8L)|address.GetAddress(i);
    }
    addr.sin_addr.s_addr=htonl(my_addr);
    addr.sin_port = htons(address.GetPort());

    //effettuo il bind dell'indirizzo
    int result=bind(_Socket, (sockaddr *)&addr, sizeof(sockaddr_in));
    _HasBind = (result == 0);

    return _HasBind;
}

void TcpSocketComponent::Close(){
	close(_Socket);
	_IsConnected = false;
	_Socket = -1;
}

bool TcpSocketComponent::Connect(const NetAddress & address){
//TODO connect for client
	struct sockaddr_in serv_addr;
	struct hostent *server;

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(address.GetPort());

	std::string addr = address.ToString();
	addr = addr.substr(0,addr.find(":"));

	//Ottenimento host da hostname/ip address
	server = gethostbyname(addr.c_str());
	if(server == NULL){

		return false;
	}
	memcpy((char*)&serv_addr.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
	//Connessione con il server tcp
	if(connect(_Socket,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        _IsConnected = false;
#ifdef DEBUG
		std::cerr << "Connection error" << std::endl;
#endif
        return false;
	}
	_IsConnected = true;
	return true;
}

int TcpSocketComponent::Read(unsigned char* buffer, unsigned int size){
    if(!_IsConnected){
#ifdef DEBUG
        std::cerr << "Read Error: Not Connected" << _Socket <<std::endl;
#endif
        return -1;
    }

    int read_bytes = recv(_Socket, buffer, size, 0);
    if(read_bytes <= 0){
#ifdef DEBUG
        std::cerr << "Read Error for socket:" << _Socket <<std::endl;
#endif
    }
    return read_bytes;
}

int TcpSocketComponent::Write(const unsigned char *buffer, unsigned int size){
    if(!_IsConnected){
#ifdef DEBUG
        std::cerr << "Write Error: Not Connected" << _Socket <<std::endl;
#endif
    	return -1;
    }
    std::cerr << "Start Sending" << std::endl;
    int wrote_bytes=send(_Socket, (char *)buffer, size, 0);
    std::cerr << "End Sending" << std::endl;
    if (wrote_bytes < 0){
#ifdef DEBUG
        std::cerr << "Write Error" << std::endl;
#endif
    }
    return wrote_bytes;
}


bool TcpSocketComponent::Listen(){
    if (!_HasBind) return (false);
    return ( (listen(_Socket,10)) == 0);
}

bool TcpSocketComponent::CreateSocket(){
	//Crazione socket della famiglia INET
	int optval = 1;
	_Socket = socket(AF_INET, SOCK_STREAM, 6);
	if(_Socket < 0){
		_IsConnected = false;
		#ifdef DEBUG
			std::cerr << "socket function error" << std::endl;
		#endif
	}else{
	    setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof (optval));
	    _IsConnected = true;
	}

	return _Socket > 0;
}
