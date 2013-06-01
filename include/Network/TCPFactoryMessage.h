/*
 * SimpStimpProject: TCPFactoryMessage.h
 *
 *  Created on: 08/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef TCPFACTORYMESSAGE_H_
#define TCPFACTORYMESSAGE_H_

#include <string>
#include <vector>

#include "global_types.h"

class TCPFactoryMessage {
public:
	static std::vector<char> CreateTcpMessage(const EN_MSG_IDENTFIER &id, const char* body, const UINT32 &msg_size = 0);
};

#endif /* TCPFACTORYMESSAGE_H_ */
