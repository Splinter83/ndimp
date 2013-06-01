/*
 * SimpStimpProject: GenericActiveEventListener.h
 *
 *  Created on: 05/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef GENERICACTIVEEVENTLISTENER_H_
#define GENERICACTIVEEVENTLISTENER_H_

#include "GenericEventListener.h"
#include "ActiveObject.h"
#include "IActiveObjectCommand.h"
#include "BaseRunnableThread.h"

template<typename T, typename TL> struct ActiveMessage: public IActiveObjectCommand{

	ActiveMessage(const T& msg, IMultipleListener<TL> * listener): _Msg(msg), _Listener(listener){
		assert(_Listener);
	}

    ~ActiveMessage(){}

    void Destroy(){
    	delete this;
    }

    void Execute(ActiveObject * context){
    	_Listener->Handle(_Msg);
    }

private:
    const T _Msg;
    IMultipleListener<TL> * _Listener;
};

template<typename T, typename Base> class ActiveMultipleListenerElement: public Base{
public:
	inline void Handle(const T & msg){
        Base::QueueMessage(msg);
	}

    template <typename H> inline void Handle(const H & msg){
    	// Redirect to Base class in case msg is not of T type.
        Base::Handle(msg);
    }
};

template<typename T, typename TL> class ActiveMultipleListenerElement<T, IMultipleListener<TL> >: public IMultipleListener<TL>{
public:
	inline void Handle(const T & msg){
		QueueMessage(msg);
	}

    template <typename H> inline void Handle(const H & msg){
    	assert(false);
    }

protected:
    template <typename H> inline void QueueMessage(const H & msg){
		ActiveObject* activeObj = GetActiveObject();
		assert(activeObj);

		activeObj->QueueCommand(new ActiveMessage<H, TL>(msg, GetMultipleListener()));
    }

protected:
	virtual ActiveObject* GetActiveObject() = 0;

	virtual IMultipleListener<TL> * GetMultipleListener() = 0;

};

template<typename TL> class ActiveMultipleListener: public InterfaceImplementation<ActiveMultipleListenerElement, TL,  IMultipleListener<TL> >{
public:
	ActiveMultipleListener(char * name): _Listener(NULL), _ActiveObject(name){
	}

	ActiveMultipleListener(IMultipleListener<TL> * listener, char * name):
		_Listener(listener),
		_ActiveObject(name){
		assert(_Listener);
	}

	virtual ~ActiveMultipleListener(){
		Stop();
	}

    virtual void Start(){
    	_ActiveObject.Start();
    }

    virtual void Stop(){
    	_ActiveObject.Stop();
    }

protected:
	ActiveObject * GetActiveObject(){
		return &_ActiveObject;
	}

	IMultipleListener<TL> * GetMultipleListener(){
		return _Listener;
	}

private:
	IMultipleListener<TL> * _Listener;
	ActiveObject _ActiveObject;
};



#endif /* GENERICACTIVEEVENTLISTENER_H_ */
