/*
 * SimpStimpProject: CommandResultFactory.cpp
 *
 *  Created on: 04/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "CommandResultFactory.h"
#include <ostream>
#include "CommandStatus.hxx"



std::string CommandResultFactory::CreateCmdResultXML(const CmdResult &cmdResult){
	std::ostringstream oss;
	xml_schema::namespace_infomap map;
	map[""].name = "";
	map["xsn"].name = "http://www.w3.org/2001/XMLSchema-instance";
	map[""].schema = XSD_PATH_NAME "CommandStatus.xsd";

	cs::CommandStatus cmd_xml(0,0,false);
	cmd_xml.Result(cmdResult.GetField(&CmdResultField::tMsgParameters::Result));
	cmd_xml.CurrentStep(cmdResult.GetField(&CmdResultField::tMsgParameters::CurrentStep));
	cmd_xml.IsTerminated(cmdResult.GetField(&CmdResultField::tMsgParameters::IsTerminated));
	if(cmdResult.GetField(&CmdResultField::tMsgParameters::Message) != '\0')
		cmd_xml.Text(cmdResult.GetField(&CmdResultField::tMsgParameters::Message));

	cs::CommandStatus_(oss,cmd_xml,map);
	return oss.str();
}

std::string CommandResultFactory::CreateCmdResultXML(const CmdResultField &cmdResult){
	CmdResult cmd_converted;
	cmd_converted(cmdResult);
	return CreateCmdResultXML(cmd_converted);
}
