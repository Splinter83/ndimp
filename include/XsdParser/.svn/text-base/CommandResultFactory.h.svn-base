/*
 * SimpStimpProject: CommandResultFactory.h
 *
 *  Created on: 04/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef COMMANDRESULTFACTORY_H_
#define COMMANDRESULTFACTORY_H_

#include "MessageXml.h"
#include "global_definitions.h"
#include "global_types.h"

#include <string>

typedef FieldSetter<CmdResultField> CmdResult;

class CommandResultFactory {
public:
	static std::string CreateCmdResultXML(const CmdResult &cmdResult);
	static std::string CreateCmdResultXML(const CmdResultField &cmdResult);
};

#endif /* COMMANDRESULTFACTORY_H_ */
