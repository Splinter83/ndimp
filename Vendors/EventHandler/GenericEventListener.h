#ifndef _GENERIC_EVENT_LISTENER_H_
#define _GENERIC_EVENT_LISTENER_H_

#include "TypeList.h"
#include "MultipleInterface.h"
#include "InterfaceImplementation.h"

#include <assert.h>
#include <iostream>
#include <vector>

template <typename T> class IListener
{

public:

	virtual ~IListener() {}

	virtual void Handle(const T & msg)=0;

};

template <typename TL> class IMultipleListener : public MultipleInterface<IListener, TL>
{

public:

	virtual ~IMultipleListener() {}

	template <typename H> void Handle(const H & msg)
    {
		(static_cast<IListener<H> *>(this))->Handle(msg);
    }

};

template <typename T> class IGenericNotifier
{

public:

	virtual ~IGenericNotifier() {}

    virtual void AddListener(IListener<T> * listener)=0;

    virtual void RemoveListener(IListener<T> * listener)=0;

    virtual void NotifyListeners(const T & msg)=0;

};

template <typename TL> class IMultipleNotifier;

template <typename TL, typename H, typename K> struct AddListenersToNotifierStruct;

template <typename Head, typename Tail, typename H, typename K> struct AddListenersToNotifierStruct<TypeList<Head, Tail>, H, K>
{

public:

	static void  AddListenersToNotifier(H listener, K notifier)
	{
		IListener<Head> * t_listener = dynamic_cast<IListener<Head> *>(listener);
	    if (t_listener)
		    notifier->AddListener(t_listener);

	    AddListenersToNotifierStruct<Tail, H, K>::AddListenersToNotifier(listener, notifier);
	}

};

template <typename Head, typename H, typename K> struct AddListenersToNotifierStruct<TypeList<Head, NullType>, H, K>
{

public:

	static void  AddListenersToNotifier(H listener, K notifier)
	{
	    IListener<Head> * t_listener = dynamic_cast<IListener<Head> *>(listener);
	    if (t_listener)
		    notifier->AddListener(t_listener);
	}

};

template <typename TL, typename H, typename K> struct RemoveListenersToNotifierStruct;

template <typename Head, typename Tail, typename H, typename K> struct RemoveListenersToNotifierStruct<TypeList<Head, Tail>, H, K>
{

public:

	static void  RemoveListenersToNotifier(H listener, K notifier)
	{
	    IListener<Head> * t_listener = dynamic_cast<IListener<Head> *>(listener);
	    if (t_listener)
		    notifier->RemoveListener(t_listener);

	    RemoveListenersToNotifierStruct<Tail, H, K>::RemoveListenersToNotifier(listener, notifier);
	}

};

template <typename Head, typename H, typename K> struct RemoveListenersToNotifierStruct<TypeList<Head, NullType>, H, K>
{

public:

	static void  RemoveListenersToNotifier(H listener, K notifier)
	{
	    IListener<Head> * t_listener = dynamic_cast<IListener<Head> *>(listener);
	    if (t_listener)
		    notifier->RemoveListener(t_listener);
	}

};

template <typename TL> class IMultipleNotifier : public MultipleInterface<IGenericNotifier, TL>
{

public:

	virtual ~IMultipleNotifier() {}

    template <typename H> void AddListener(IListener<H> * listener)
    {
		(static_cast<IGenericNotifier<H> *>(this))->AddListener(listener);
    }

    template <typename H> void RemoveListener(IListener<H> * listener)
    {
		(static_cast<IGenericNotifier<H> *>(this))->RemoveListener(listener);
    }

    template <typename H> void NotifyListeners(const H &p)
	{
		(static_cast<IGenericNotifier<H> *>(this))->NotifyListeners(p);
	}

    template <typename H> inline void AddListeners(H listener)
	{
    	AddListenersToNotifierStruct<TL, H, IMultipleNotifier<TL>* >::AddListenersToNotifier(listener, this);
	}

    template <typename H> inline void RemoveListeners(H listener)
	{
    	RemoveListenersToNotifierStruct<TL, H, IMultipleNotifier<TL>* >::RemoveListenersToNotifier(listener, this);
	}

};

template <typename T> class GenericNotifier: public IGenericNotifier<T>
{

public:

	virtual ~GenericNotifier() {}

    void AddListener(IListener<T> * listener)
    {
       _Listeners.push_back(listener);
    }

	void RemoveListener(IListener<T> * listener)
	{
		typename std::vector<IListener<T> *>::iterator iter=_Listeners.begin();
		while (iter != _Listeners.end())
		{
			if (*iter == listener)
			{
				_Listeners.erase(iter);
				break;
			}
			iter++;
		}
	}

	void NotifyListeners(const T & msg)
    {
		typename std::vector<IListener<T> *>::const_iterator iter=_Listeners.begin();
		while (iter != _Listeners.end())
        {
			(*iter)->Handle(msg);
			iter++;
        }
    }

private:

	std::vector<IListener<T> * > _Listeners;

};

template <typename T, typename Base> class GenericNotifierElement : public Base
{

public:

	virtual ~GenericNotifierElement(){}

    inline void AddListener(IListener<T> * listener)
    {
    	_Notifier.AddListener(listener);
    }

    inline void RemoveListener(IListener<T> * listener)
    {
    	_Notifier.RemoveListener(listener);
    }

    inline void NotifyListeners(const T & msg)
    {
    	_Notifier.NotifyListeners(msg);
    }

    template <typename H> inline void AddListener(IListener<H> * listener)
    {
        Base::AddListener(listener);
    }

    template <typename H> inline void RemoveListener(IListener<H> * listener)
    {
        Base::RemoveListener(listener);
    }

    template <typename H> inline void NotifyListeners(const H & msg)
    {
        Base::NotifyListeners(msg);
    }

private:

	GenericNotifier<T> _Notifier;

};

template <typename T, typename TL> class GenericNotifierElement<T, IMultipleNotifier<TL> > : public IMultipleNotifier<TL>
{

public:

	virtual ~GenericNotifierElement(){}

    inline void AddListener(IListener<T> * listener)
    {
    	_Notifier.AddListener(listener);
    }

    inline void RemoveListener(IListener<T> * listener)
    {
    	_Notifier.RemoveListener(listener);
    }

    inline void NotifyListeners(const T & msg)
    {
    	_Notifier.NotifyListeners(msg);
    }

    template <typename H> inline void AddListener(IListener<H> * listener){}

    template <typename H> inline void RemoveListener(IListener<H> * listener){}

    template <typename H> inline void NotifyListeners(const H & msg){}

private:

	  GenericNotifier<T> _Notifier;

};

template <typename InTL> class MultipleNotifier: public InterfaceImplementation<GenericNotifierElement, InTL, IMultipleNotifier<InTL> >
{

public:

	virtual ~MultipleNotifier() {}

};

template <typename T, typename Base> class NotifierElement: public Base
{

public:

	virtual ~NotifierElement() {}

	inline void AddListener(IListener<T> * listener){
    	Base::AddListener(listener);
    }

    inline void RemoveListener(IListener<T> * listener){
    	Base::RemoveListener(listener);
    }

    inline void NotifyListeners(const T & msg){
 		Base::NotifyListeners(msg);
    }

	template<typename H> inline void AddListener(IListener<H> * listener){
    	Base::AddListener(listener);
    }

	template<typename H> inline void RemoveListener(IListener<H> * listener){
 		Base::RemoveListener(listener);
    }

	template<typename H> inline void NotifyListeners(const H & msg){
 		Base::NotifyListeners(msg);
    }

};

template <typename TL> class NotifierElementBase: public IMultipleNotifier<TL>
{

public:

	virtual ~NotifierElementBase() {}

	template<typename H> inline void AddListener(IListener<H> * listener){
		IMultipleNotifier<TL> * notifier = GetNotifier();
		assert(notifier);
		notifier->AddListener(listener);
    }

	template<typename H> inline void RemoveListener(IListener<H> * listener){
		IMultipleNotifier<TL> * notifier = GetNotifier();
		assert(notifier);
		notifier->RemoveListener(listener);
    }

	template<typename H> inline void NotifyListeners(const H & msg){
		IMultipleNotifier<TL> * notifier = GetNotifier();
		assert(notifier);
		notifier->NotifyListeners(msg);
    }

protected:

	virtual IMultipleNotifier<TL> * GetNotifier() = 0;

};

#endif

