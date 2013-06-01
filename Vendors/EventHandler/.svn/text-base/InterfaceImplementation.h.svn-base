#ifndef _INTERFACE_IMPLEMENTATION_H_
#define _INTERFACE_IMPLEMENTATION_H_

#include "TypeList.h"

/*
 * InterfaceImplementation
 */
template<template<class, class > class Element, typename TL, typename Root> class InterfaceImplementation;

/*
 * Specialization of InterfaceImplementation for not empty list
 */
template<template<class, class > class Element, typename Head, typename Tail,
		typename Root>
class InterfaceImplementation<Element, TypeList<Head, Tail>, Root> : public Element<
		Head, InterfaceImplementation<Element, Tail, Root> > {
public:
	typedef Element<Head, InterfaceImplementation<Element, Tail, Root> > Base;

	InterfaceImplementation<Element, TypeList<Head, Tail>, Root>() {
	}

	virtual ~InterfaceImplementation<Element, TypeList<Head, Tail>, Root>() {
	}
};

/*
 * Specialization of InterfaceImplementation for head element
 */
template<template<class, class > class Element, typename Head, typename Root>
class InterfaceImplementation<Element, TypeList<Head, NullType>, Root> : public Element<
		Head, Root> {
public:
	typedef Element<Head, Root> Base;

	InterfaceImplementation<Element, TypeList<Head, NullType>, Root>() {
	}

	~InterfaceImplementation<Element, TypeList<Head, NullType>, Root>() {
	}
};

#endif

