/*
 * SimpStimpProject: IGenericContext.h
 *
 *  Created on: 01/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef IGENERICCONTEXT_H_
#define IGENERICCONTEXT_H_

#include "GenericEventListener.h"

template<typename EventsTL> class IGenericState;

template<typename EventsTL> class IGenericContext : public IMultipleListener<EventsTL>{
	public:
		virtual ~IGenericContext(){}

	public:
		virtual void ChangeState(IGenericState<EventsTL> * newState) = 0;

		virtual IGenericState<EventsTL> * GetCurrentState(void) const = 0;

		virtual IGenericState<EventsTL> * GetPreviousState(void) const = 0;
};

#endif /* IGENERICCONTEXT_H_ */


