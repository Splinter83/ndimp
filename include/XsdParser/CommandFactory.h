/*
 * CommandXmlAdapter.h
 *
 *  Created on: 21/giu/2012
 *      Author: emanuele_galli
 */

#ifndef COMMANDFACTORY_H_
#define COMMANDFACTORY_H_

#include <sstream>

#include "MessageXml.h"
#include "global_definitions.h"
#include "global_types.h"
#include "Command.hxx"

#include <string>
#include <memory>
#include <vector>


typedef FieldSetter<CmdMessageField> CommandMessage;


class CommandFactory {
public:
	static std::vector<CommandMessage> ParseStream(::std::istringstream &is) throw(xml_schema::exception&) ;
};

#endif /* COMMANDFACTORY_H_ */
