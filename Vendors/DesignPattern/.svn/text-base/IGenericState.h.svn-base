/*
 * IGenericState.h
 *
 *  Created on: 01/ott/2012
 *  Author: Emanuele Galli
 */

#ifndef IGENERICSTATE_H_
#define IGENERICSTATE_H_

#include "GenericEventListener.h"
#include "BaseStateEvent.h"

template<typename EventsTL> class IGenericContext;

template<typename EventsTL> class IGenericState : public IMultipleListener<EventsTL>{
	public:
		virtual ~IGenericState(){}

	public:
		virtual void SetContext(IGenericContext<EventsTL> * context) = 0;

		virtual IGenericContext<EventsTL> * GetContext(void) const = 0;

		virtual void Handle(const OnEntryEvent & msg) = 0;

		virtual void Handle(const OnExitEvent & msg) = 0;

		template <typename H> void Handle(const H & msg)
	    {
			(static_cast<IListener<H> *>(this))->Handle(msg);
	    }
};

#endif /* IGENERICSTATE_H_ */
