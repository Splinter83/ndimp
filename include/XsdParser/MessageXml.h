/*
 * MessageXml.h
 *
 *  Created on: 26/giu/2012
 *  Author: emanuele_galli
 */

#ifndef _MESSAGEXML_H
#define _MESSAGEXML_H

#include "global_definitions.h"

/**
 * @class Template class that provides SET and GET method for a given struct
 */
template<class MsgFields/*, class MutexPolicy*/>
class FieldSetter {
public:
	typedef MsgFields tMsgFields;
	typedef typename MsgFields::tMsgParameters tMsgParameters;

	/**
	 * Function overloading to convert a tMsgParameters to a FieldSetter class
	 * @param params tMsgParameters
	 * @return Calling class with new argument data
	 */
	FieldSetter operator() (const tMsgParameters &params) {
		memcpy(this->_params, params, sizeof(this->_params));
		return *this;
	}

	/**
	 * Function overloading to convert a MsgFields to a FieldSetter class
	 * @param params MsgFields
	 * @return Calling class with new argument data
	 */
	FieldSetter operator() (const MsgFields &msg) {
		memcpy(&this->_params, (tMsgParameters*) &msg, sizeof(this->_params));
		return *this;
	}

	/**
	 * Casting overloading from FieldSetter to tMsgParameters
	 */
	operator tMsgParameters(){
		return this->_params;
	}

	/**Casting overloading from FieldSetter to MsgFields
	 *
	 */
	operator MsgFields(){
		MsgFields ret;
		memcpy(&ret,&(this->_params),sizeof(this->_params));
		return ret;
	}


protected:
	tMsgParameters _params;

public:
	/**
	 * Gets current value from the argument filed into tMsgParameters struct
	 * @param field Field in tMsgParameters
	 * @return Current value in field argument
	 */
	template<typename FieldType>
	const FieldType & GetField(FieldType tMsgParameters::* field) const {
		return _params.*field;
	}

	/**
	 * Sets value argument from into filed of tMsgParameters struct
	 * @param field Field to be set
	 * @param value Value to be set
	 */
	template<typename FieldType>
	void SetField(FieldType tMsgParameters::* field, FieldType value) {

		if (_params.*field != value) {
			_params.*field = value;
		}
	}

	template<typename BaseType,typename FieldType>
	void SetMemory(FieldType tMsgParameters::* field, unsigned int size){
		if(_params.*field != NULL)
			delete [] &(_params.*field);
		(_params.*field) = new BaseType[size];
	}

	template<typename FieldType>
	void SetArray(FieldType* tMsgParameters::* field,const FieldType *value, unsigned int size){
		for(unsigned int i = 0; i < size; ++i)
			(_params.*field)[i] = value[i];
	}
};

#endif  //_MESSAGEXML_H
