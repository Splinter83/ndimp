/*
 * CommandFactory.cpp
 *
 *  Created on: 21/giu/2012
 *      Author: emanuele_galli
 */

#include "CommandFactory.h"
#include <iostream>
#include <sstream>
#include "Utils.h"
#include "Logger.h"


std::vector<CommandMessage> CommandFactory::ParseStream(::std::istringstream &is) throw(xml_schema::exception&){
        // TODO Auto-generated constructor stub
        std::vector<CommandMessage> cmdList;
        std::auto_ptr<cs::CommandList> xmlCommandList;
        UINT32 value = 0;
        xml_schema::properties props;

        props.no_namespace_schema_location (XSD_PATH_NAME "Command.xsd");

        try{
            xmlCommandList = cs::CommandList_(is,0,props);

			unsigned int count = 0;
			CommandMessage command;

			while(count < xmlCommandList->Command().size()){
				memset(&command,0,sizeof(CommandMessage));
				cs::CommandType xmlcommand = xmlCommandList->Command().at(count);
				std::string str_id = xmlcommand.id().substr(xmlcommand.id().find("_") + 1);
				value = Utils::lexical_cast<UINT32>(str_id.c_str());
				command.SetField(&CmdMessageField::tMsgParameters::ID,value);
				if(xmlcommand.Board().find("SIMP1") != std::string::npos)
					command.SetField(&CmdMessageField::tMsgParameters::Board, ::SIMP1);
				else if(xmlcommand.Board().find("SIMP2") != std::string::npos)
					command.SetField(&CmdMessageField::tMsgParameters::Board, ::SIMP2);
				else if(xmlcommand.Board().find("STIMP") != std::string::npos)
					command.SetField(&CmdMessageField::tMsgParameters::Board, ::STIMP);
				else if(xmlcommand.Board().find("OTHER") != std::string::npos)
					command.SetField(&CmdMessageField::tMsgParameters::Board, ::OTHER);
				//CONFIGURATION COMMAND
				if(xmlcommand.Config().present()){
					command.SetField(&CmdMessageField::tMsgParameters::Command,CONFIG);
					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Config().get().BaseAddress().encode());
					command.SetField(&CmdMessageField::tMsgParameters::BaseAddress,value );
					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Config().get().RAMsize().encode());
					command.SetField(&CmdMessageField::tMsgParameters::RamSize,value );
					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Config().get().Arbitered_IO().encode());
					command.SetField(&CmdMessageField::tMsgParameters::Arbitered_IO,value );
					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Config().get().Direct_IO().encode());
					command.SetField(&CmdMessageField::tMsgParameters::Direct_IO,value );
					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Config().get().Restart_HS().encode());
					command.SetField(&CmdMessageField::tMsgParameters::Restart_HS,value );

					if(xmlcommand.Config().get().RTAddress().present()){
						command.SetField(&CmdMessageField::tMsgParameters::RT_Address,(UINT8)xmlcommand.Config().get().RTAddress().get() );
				    }
					else{
						command.SetField(&CmdMessageField::tMsgParameters::RT_Address,(UINT8)0xFF);
					}
					/** TODO
					 * Utilizzare lo switch
					 */
					if(xmlcommand.Config().get().InterfaceName().find("AVIONIC") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Interface,AVIONIC);
				    else if(xmlcommand.Config().get().InterfaceName().find("BSD") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Interface,BSD);
				    else if(xmlcommand.Config().get().InterfaceName().find("MDP") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Interface,MDP);
				    else if(xmlcommand.Config().get().InterfaceName().find("CSMU") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Interface,CSMU);
				    else if(xmlcommand.Config().get().InterfaceName().find("ATTACK") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Interface,ATTACK);
				    else if(xmlcommand.Config().get().InterfaceName().find("EMU1") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Interface,EMU1);
				    else if(xmlcommand.Config().get().InterfaceName().find("EMU2") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Interface,EMU2);
				    else if(xmlcommand.Config().get().InterfaceName().find("UCS") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Interface,UCS);
				    else if(xmlcommand.Config().get().InterfaceName().find("UNK") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Interface,UNK);
				    if(xmlcommand.Config().get().Type().find("NONE") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Component,::CMP_NONE);
				    else if(xmlcommand.Config().get().Type().find("3838") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Component,::CMP_3838);
				    else if(xmlcommand.Config().get().Type().find("3910") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Component,::CMP_3910);
				    else if(xmlcommand.Config().get().Type().find("ODDL") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Component,::CMP_ODDL);
				    else if(xmlcommand.Config().get().Type().find("EDDL") != std::string::npos)
				    	command.SetField(&CmdMessageField::tMsgParameters::Component,::CMP_EDDL);

					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Config().get().BITHistory_Addr().encode());
					command.SetField(&CmdMessageField::tMsgParameters::BIT_History_Addr,value );
					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Config().get().BITHistory_Size().encode());
					command.SetField(&CmdMessageField::tMsgParameters::BIT_History_Size,value );
				}
				//READ COMMAND
				else if(xmlcommand.Read().present()){
					command.SetField(&CmdMessageField::tMsgParameters::Command,READ);
					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Read().get().Address().encode());
					command.SetField(&CmdMessageField::tMsgParameters::Address, value);
					if(xmlcommand.Read().get().Alignment().present()){
						switch(xmlcommand.Read().get().Alignment().get()){
						    case cs::Alignment::B:
						    	command.SetField(&CmdMessageField::tMsgParameters::Alignment,EN_VME_BYTE);
						    break;
						    case cs::Alignment::W:
						    	command.SetField(&CmdMessageField::tMsgParameters::Alignment,EN_VME_WORD);
						    break;
						    case cs::Alignment::D:
						    	command.SetField(&CmdMessageField::tMsgParameters::Alignment,EN_VME_DOUBLE_WORD);
						    break;
						}
					}
					else{
						command.SetField(&CmdMessageField::tMsgParameters::Alignment,EN_VME_WORD);
					}
				}
				//WRITE COMMAND
				else if(xmlcommand.Write().present()){
					command.SetField(&CmdMessageField::tMsgParameters::Command,WRITE);
					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Write().get().Address().encode());
					command.SetField(&CmdMessageField::tMsgParameters::Address, value);
					value = Utils::cast_from_hex<UINT32>("0x"+xmlcommand.Write().get().Data().encode());
					command.SetField(&CmdMessageField::tMsgParameters::Data, value);
					if(xmlcommand.Write().get().Alignment().present()){
						switch(xmlcommand.Write().get().Alignment().get()){
						    case cs::Alignment::B:
						    	command.SetField(&CmdMessageField::tMsgParameters::Alignment,EN_VME_BYTE);
						    break;
						    case cs::Alignment::W:
						    	command.SetField(&CmdMessageField::tMsgParameters::Alignment,EN_VME_WORD);
						    break;
						    case cs::Alignment::D:
						    	command.SetField(&CmdMessageField::tMsgParameters::Alignment,EN_VME_DOUBLE_WORD);
						    break;
						}
					}
					else{
						command.SetField(&CmdMessageField::tMsgParameters::Alignment,EN_VME_WORD);
					}
				}
				//TEST COMMAND
				else if(xmlcommand.Test().present()){
					command.SetField(&CmdMessageField::tMsgParameters::Command,TEST);
					command.SetField(&CmdMessageField::tMsgParameters::TestNumber, xmlcommand.Test().get().TestNumber());
					command.SetField(&CmdMessageField::tMsgParameters::StepNumber, xmlcommand.Test().get().StepNumber().get());

					if(xmlcommand.Test().get().Channel().present()){
						switch(xmlcommand.Test().get().Channel().get()){
							case cs::Channel::CHANNEL_A:
								command.SetField(&CmdMessageField::tMsgParameters::Channel, EN_CHANNEL_A);
							break;
							case cs::Channel::CHANNEL_B:
								command.SetField(&CmdMessageField::tMsgParameters::Channel, EN_CHANNEL_B);
							break;
						}
					}

					switch(xmlcommand.Test().get().TestEnum()){
						case cs::TestEnum::SIMP1_AVIONIC_3910 :
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, SIMP1_AVIONIC_3910);
						break;
						case cs::TestEnum::SIMP1_BSD_EDDL :
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, SIMP1_BSD_EDDL);
						break;
						case cs::TestEnum::SIMP1_CSMU_EDDL :
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, SIMP1_CSMU_EDDL);
						break;
						case cs::TestEnum::SIMP1_MDP_EDDL :
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, SIMP1_MDP_EDDL);
						break;
						case cs::TestEnum::SIMP2_ATTACK_3910 :
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, SIMP2_ATTACK_3910);
						break;
						case cs::TestEnum::SIMP2_EMU1_EDDL :
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, SIMP2_EMU1_EDDL);
						break;
						case cs::TestEnum::SIMP2_EMU2_EDDL :
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, SIMP2_EMU2_EDDL);
						break;
						case cs::TestEnum::SIMP2_UCS_3838:
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, SIMP2_UCS_3838);
						break;
						case cs::TestEnum::STIMP_ATTACK_3910:
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, STIMP_ATTACK_3910);
						break;
						case cs::TestEnum::STIMP_AVIONIC_3910:
							command.SetField(&CmdMessageField::tMsgParameters::ConfigurationType, STIMP_AVIONIC_3910);
						break;
						default:
							std::terminate();
						break;
					}

					if(xmlcommand.Test().get().TerminalNumber().present()){
						command.SetField(&CmdMessageField::tMsgParameters::RT_Address, (UINT8)xmlcommand.Test().get().TerminalNumber().get());
					}
					else{
						command.SetField(&CmdMessageField::tMsgParameters::RT_Address,(UINT8)0xFF);
					}

					if(xmlcommand.Test().get().RCI().present()){
						command.SetField(&CmdMessageField::tMsgParameters::RCI, (UINT8)xmlcommand.Test().get().RCI().get());
					}
				}
				++count;
				cmdList.push_back(command);
			}
        }catch (const xml_schema::exception& e){
            std::cerr << e << std::endl;
            std::cerr << "input :" << std::endl;
            std::cerr << is.str() << std::endl;
        	throw &e;
                //exit(1);
        }

        return cmdList;
}
