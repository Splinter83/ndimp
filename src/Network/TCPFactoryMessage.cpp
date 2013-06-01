/*
 * SimpStimpProject: TCPFactoryMessage.cpp
 *
 *  Created on: 08/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "TCPFactoryMessage.h"
#include "global_definitions.h"

#include <string.h>

std::vector<char> TCPFactoryMessage::CreateTcpMessage(const EN_MSG_IDENTFIER &id, const char* body, const UINT32 &msg_size){
	static const UINT32 HEADER_SIZE = sizeof(Header);
	char *message = NULL;
	Header head;
	UINT32 tot_size = 0;
	std::vector<char> ret;

	//Sets of header
	head.start_delimiter = Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("HEADER_DELIMETER", hexadecimal);
	head.identifier = id;
	head.msg_size = msg_size;

	//Fill message with header and body xml message
	tot_size = HEADER_SIZE + msg_size;
	message = new char[tot_size];
	memcpy(message,&head,sizeof(head));
	memcpy(message + HEADER_SIZE,body,head.msg_size);

	for(UINT32 i = 0; i < tot_size;++i){
		ret.push_back(message[i]);
	}

    delete[] message;
	return ret;
}
