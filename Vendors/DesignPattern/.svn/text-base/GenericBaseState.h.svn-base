/*
 * SimpStimpProject: GenericBaseState.h
 *
 *  Created on: 01/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef GENERICBASESTATE_H_
#define GENERICBASESTATE_H_

#include "TypeList.h"
#include "InterfaceImplementation.h"
#include "IGenericState.h"
#include "IGenericContext.h"
#include <assert.h>

template <typename T, typename Base> class GenericBaseStateElement: public Base{
	public:
		inline void Handle(const T & msg){
		 	// Assert - default behaviour
			assert(false);
		}

		template <typename H> inline void Handle(const H & msg){
			// Redirect to Base class in case msg is not of T type.
			Base::Handle(msg);
			}
};

template <typename T, typename TL> class GenericBaseStateElement<T, IGenericState<TL> > : public IGenericState<TL>{
	public:
	    inline void Handle(const T & msg){
	    	// Assert - default behaviour
	    	assert(false);
	    }

	    template <typename H> inline void Handle(const H & msg){
	    	// Assert - this msg type is not expected
	    	assert(false);
	    }
};

template<typename EventsTL> class GenericBaseState : public InterfaceImplementation<GenericBaseStateElement, EventsTL, IGenericState<EventsTL> >{
	public:
		GenericBaseState(): _Context(NULL){}

		virtual ~GenericBaseState(){}

	public:
		inline void SetContext(IGenericContext<EventsTL> * context){
			assert(context);
			_Context = context;
		}

		inline IGenericContext<EventsTL> * GetContext(void) const{
			return _Context;
		}

		inline void Handle(const OnEntryEvent & msg){
			//Do Nothing - default behaviour
		}

		inline void Handle(const OnExitEvent & msg){
			//Do Nothing - default behaviour
		}

	protected:
		void ChangeState(IGenericState<EventsTL>* newState) const{
			assert(_Context);
			assert(newState);
			_Context->ChangeState(newState);
		}

	private:
		IGenericContext<EventsTL> * _Context;
};
#endif /* GENERICBASESTATE_H_ */
