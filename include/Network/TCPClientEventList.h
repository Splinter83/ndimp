/*
 * SimpStimpProject: TCPClientEventList.h
 *
 *  Created on: 08/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef TCPCLIENTEVENTLIST_H_
#define TCPCLIENTEVENTLIST_H_

#include "TsapEvents.h"
#include "TypeList.h"

typedef TYPELIST_2(
			LogMsgEvent,
			DiscreteEvent
		) tClientListenableEventList;


#endif /* TCPCLIENTEVENTLIST_H_ */
