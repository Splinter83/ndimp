/*
 * NetAddress.cpp
 *
 *  Created on: 20/giu/2012
 *      Author: emanuele_galli
 */

#include "NetAddress.h"
#include <stdio.h>
#include <assert.h>

NetAddress::NetAddress() {
	for (int i = 0; i < 4; i++)
		_Address[i] = 0;
	_Port = 0;
}

NetAddress::~NetAddress() {
	// TODO Auto-generated destructor stub
}

NetAddress::NetAddress(unsigned short port) {
	_Port = port;
	for (int i = 0; i < 4; i++)
		_Address[i] = 0;

}

NetAddress::NetAddress(const char* addr) {
	int a0,a1,a2,a3,a4;
	int matches=sscanf(addr,"%d.%d.%d.%d:%d",&a0,
                                             &a1,
                                             &a2,
                                             &a3,&a4);
    assert(matches == 5);

	_Address[0]=a0;
    _Address[1]=a1;
    _Address[2]=a2;
    _Address[3]=a3;
    _Port=a4;

}

NetAddress::NetAddress(const unsigned char *addr, unsigned short port) {
    for (int i=0; i<4; i++)
       _Address[i]=addr[i];
	_Port = port;
}

std::string NetAddress::ToString() const {
	char buffer[256];
	sprintf(buffer, "%u.%u.%u.%u:%u", _Address[0], _Address[1], _Address[2],
			_Address[3], _Port);
	std::string result(buffer);
	return result;
}

NetAddress & NetAddress::operator=(const NetAddress & right) {
	if (this != &right) {
		_Port = right._Port;
		for (int i = 0; i < 4; ++i)
			_Address[i] = right._Address[i];
	}

	return *this;
}
