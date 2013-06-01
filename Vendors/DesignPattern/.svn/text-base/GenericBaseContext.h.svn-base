/*
 * SimpStimpProject: GenericBaseContext.h
 *
 *  Created on: 02/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef GENERICBASECONTEXT_H_
#define GENERICBASECONTEXT_H_

#include "IGenericContext.h"
#include "IGenericState.h"

template<typename T, typename Base> class GenericBaseContextElement: public Base {
public:
	inline void Handle(const T & msg) {
		// Redirect to Base class in case msg is not of T type.
		Base::Forward(msg);
	}
};

template<typename T, typename EventsTL> class GenericBaseContextElement<T,
		IGenericContext<EventsTL> > : public IGenericContext<EventsTL> {
public:
	inline void Handle(const T & msg) {
		// Forward to a listener defined by the user of this element
		Forward(msg);
	}

	template<typename H> inline void Handle(const H & msg) {
		assert(false);
	}

	template<typename H> inline void Forward(const H & msg) {
		IGenericState<EventsTL> * currState = GetCurrentState();
		assert(currState);
		currState->Handle(msg);
		while (IsStateChanged()) {
			PerformChangeState();
		}
	}

	virtual IGenericState<EventsTL> * GetCurrentState(void) const = 0;

protected:
	virtual bool IsStateChanged(void) const = 0;

	virtual void PerformChangeState(void) = 0;
};

template<typename EventsTL> class GenericBaseContext: public InterfaceImplementation<
		GenericBaseContextElement, EventsTL, IGenericContext<EventsTL> > {

public:
	GenericBaseContext() :
			_CurrentState(NULL), _PreviousState(NULL), _NewState(NULL) {
	}

	virtual ~GenericBaseContext() {
	}

public:
	void ChangeState(IGenericState<EventsTL> * newState) {
		assert(newState);
		_NewState = newState;
	}

	IGenericState<EventsTL> * GetCurrentState(void) const {
		return _CurrentState;
	}

	IGenericState<EventsTL> * GetPreviousState(void) const {
		return _PreviousState;
	}

protected:
	inline bool IsStateChanged(void) const {
		return (_NewState != _CurrentState);
	}

	inline void PerformChangeState(void) {
		_PreviousState = _CurrentState;
		_CurrentState = _NewState;

		if (_PreviousState)
			_PreviousState->Handle(OnExitEvent());

		_CurrentState->Handle(OnEntryEvent());
	}

protected:
	IGenericState<EventsTL> * _CurrentState;
	IGenericState<EventsTL> * _PreviousState;
	IGenericState<EventsTL> * _NewState;
};

#endif /* GENERICBASECONTEXT_H_ */
