#ifndef _MULTIPLE_INTERFACE_H_
#define _MULTIPLE_INTERFACE_H_

#include "TypeList.h"

/*
 * MultipleInterface: class to extend an other class with multiple interfaces
 */
template<template<class > class BaseInterface, typename TL,
		class RootInterface = NullType> class MultipleInterface;

/*
 * Specialization of MultipleInterface for not empty list
 */
template<template<class > class BaseInterface, class RootInterface, typename H,
		typename T>
class MultipleInterface<BaseInterface, TypeList<H, T>, RootInterface> : public MultipleInterface<
		BaseInterface, T, RootInterface>,
		public BaseInterface<H> {
public:
	virtual ~MultipleInterface<BaseInterface, TypeList<H, T>, RootInterface>() {
	}
};

/*
 * Specialization of MultipleInterface for atomic type
 */
template<template<class > class BaseInterface, class RootInterface>
class MultipleInterface<BaseInterface, NullType, RootInterface> : public RootInterface {
public:
	virtual ~MultipleInterface<BaseInterface, NullType, RootInterface>() {
	}
};

/*
 * Specialization of MultipleInterface for null type
 */
template<template<class > class BaseInterface>
class MultipleInterface<BaseInterface, NullType, NullType> {
public:
	virtual ~MultipleInterface<BaseInterface, NullType, NullType>() {
	}
};

#endif
