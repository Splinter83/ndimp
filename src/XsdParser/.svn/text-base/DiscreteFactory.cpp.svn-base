/*
 * SimpStimpProject: DiscreteFactory.cpp
 *
 *  Created on: 02/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "DiscreteFactory.h"
#include "Discrete.hxx"
#include <ostream>

std::string DiscreteFactory::CreateDiscretetXML(std::vector<DiscreteStatus> &discVect){
	std::ostringstream oss;

	xml_schema::namespace_infomap map;
	map[""].name = "";
	map["xsn"].name = "http://www.w3.org/2001/XMLSchema-instance";
	map[""].schema = XSD_PATH_NAME "Discrete.xsd";

	cs::DiscreteType discreteXml(false,"");
	cs::DiscreteList discreteListXml;
	std::vector<DiscreteStatus>::iterator it = discVect.begin();

	while(it != discVect.end()){
		discreteXml.Name(it->GetField(&DiscreteField::tMsgParameters::Name));
		discreteXml.Status(it->GetField(&DiscreteField::tMsgParameters::Status));
		discreteListXml.DISCRETE().push_back(discreteXml);
		++it;
	}

	cs::DiscreteList_(oss,discreteListXml);
	return oss.str();
}

std::string DiscreteFactory::CreateDiscretetXML(std::vector<DiscreteField> &discVect){
	std::vector<DiscreteStatus> converted_vector;
	DiscreteStatus tmp;
	for(std::vector<DiscreteField>::iterator it = discVect.begin(); it != discVect.end(); ++it){
		tmp.SetMemory<char>(&DiscreteField::tMsgParameters::Name,MAX_BUF_SIZE);
		converted_vector.push_back(tmp(*it));
	}
	return CreateDiscretetXML(converted_vector);
}


std::string DiscreteFactory::CreateDiscretetXML(const BasicDiscreteStatusVect &discVect){
	std::ostringstream oss;

	xml_schema::namespace_infomap map;
	map[""].name = "";
	map["xsn"].name = "http://www.w3.org/2001/XMLSchema-instance";
	map[""].schema = "Discrete.xsd";

	cs::DiscreteType discreteXml(false,"");
	cs::DiscreteList discreteListXml;
	std::vector<DiscreteStruct>::const_iterator it =  discVect.begin();

	while(it != discVect.end()){
		discreteXml.Name(&(it->Name[0]));
		discreteXml.Status(it->Status);
		discreteListXml.DISCRETE().push_back(discreteXml);
		++it;
	}

	cs::DiscreteList_(oss,discreteListXml);
	return oss.str();
}
