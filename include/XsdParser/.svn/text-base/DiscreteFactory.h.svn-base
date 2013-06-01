/*
 * SimpStimpProject: DiscreteFactory.h
 *
 *  Created on: 02/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef DISCRETEFACTORY_H_
#define DISCRETEFACTORY_H_

#include "MessageXml.h"
#include "global_definitions.h"
#include "global_types.h"

#include <string>
#include <vector>

typedef FieldSetter<DiscreteField> DiscreteStatus;
typedef std::vector<DiscreteStruct> BasicDiscreteStatusVect;

/**
 * @class DiscreteFactory Factory to convert from struct of discrete status to XML
 * messages according to Discrete.xsd dictionary
 */
class DiscreteFactory {
public:
	/**
	 * Creates a XML string for discrete vector
	 * @param discVect
	 * @return A string XML representing discrete status vector argument according to Discrete.XSD
	 */
	static std::string CreateDiscretetXML(std::vector<DiscreteStatus> &discVect);

	/**
	 * Creates a XML string for discrete vector
	 * @param discVect
	 * @return A string XML representing discrete status vector argument according to Discrete.XSD
	 */
	static std::string CreateDiscretetXML(std::vector<DiscreteField>  &discVect);

	static std::string CreateDiscretetXML(const BasicDiscreteStatusVect &discVect);
};

#endif /* DISCRETEFACTORY_H_ */
