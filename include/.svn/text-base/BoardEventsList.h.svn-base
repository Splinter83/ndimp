/*
 * TsapEvents.h
 *
 *  Created on: 04/set/2012
 *  Author: Emanuele Galli
 */

#ifndef BOARDEVENTSLIST_H_
#define BOARDEVENTSLIST_H_

#include "TypeList.h"
#include "TsapEvents.h"

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
			) tBoardControlListenableEventList;

typedef TYPELIST_6(
			IdleEvent,
			ActiveEvent,
			ErrorEvent,
			ShutdownEvent,
			SGA_Event,
            CommandResultEvent
            ) tBoardControlNotifableEventList;

/*typedef TYPELIST_5(
			SGA_Event,
			WriteEvent,
			ReadEvent,
			TestsReqEvent,
			ConfigEvent
			) tBoardListenableEventList;
*/

/*typedef TYPELIST_2(
            CommandResultEvent,
            DiscreteEvent
            ) tServerNotifableEventList;
*/

#endif //BOARDEVENTSLIST_H_
