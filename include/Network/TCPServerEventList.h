/*
 * TCPServerEventList.h
 *
 *  Created on: 04/set/2012
 *      Author: grande
 */

#ifndef TCPSERVEREVENTLIST_H_
#define TCPSERVEREVENTLIST_H_

#include "TsapEvents.h"
#include "TypeList.h"

typedef TYPELIST_10(
			IdleEvent,
			ActiveEvent,
			ErrorEvent,
			ShutdownEvent,
			SGA_Event,
			WriteEvent,
			ReadEvent,
			TestsReqEvent,
			ConfigEvent,
			DiscreteEvent
			) tBoardNotifableEventList;

typedef TYPELIST_1(
		    CommandResultEvent
		)tServerListenableEventList;

#endif /* TCPSERVEREVENTLIST_H_ */
