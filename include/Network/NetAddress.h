/*
 * NetAddress.h
 *
 *  Created on: 20/giu/2012
 *      Author: emanuele_galli
 */

#ifndef NETADDRESS_H_
#define NETADDRESS_H_

#include <string>

class NetAddress {
public:
	NetAddress();
	virtual ~NetAddress();
	NetAddress(unsigned short port);
	NetAddress(const char * addr);
	NetAddress(const unsigned char *addr, unsigned short port);

	std::string ToString() const;

	unsigned char GetAddress(int i) const;
	unsigned short GetPort() const;

	NetAddress & operator=(const NetAddress & right);

private:
	unsigned char _Address[4];
	unsigned short _Port;
};

inline unsigned char NetAddress::GetAddress(int i) const {
	return _Address[i];
}

inline unsigned short NetAddress::GetPort() const {
	return _Port;
}


#endif /* NETADDRESS_H_ */
