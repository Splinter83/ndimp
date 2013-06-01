/*
 * TCPServer.cpp
 *
 *  Created on: 19/giu/2012
 *      Author: emanuele_galli
 */

#include "TCPServer.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <assert.h>
#include <string>

#include "NetAddress.h"
#include "Logger.h"
#include "Utils.h"

#include "CommandFactory.h"
#include "DiscreteFactory.h"
#include "CommandResultFactory.h"

#include "global_types.h"

#include "BoardControllerIdle.h"

#include "TCPFactoryMessage.h"
#include "TCPClient.h"
#include "Singleton.h"
#include "ConfigFile.h"

//#include "SIMP.h"
//#include "OptimizedRefined.h"
//#include "RWTestVmeAdapter.h"

TCPServer* TCPServer::_pTcpServer = NULL;

TCPServer::TCPServer() : BaseRunnableThread("TCPServer"),
                         _Buffer(0),
                         _ConnectionSocket(0){
	_netAddr = NetAddress("0.0.0.0:10001");
}

TCPServer* TCPServer::getTcpServer() {
	//TODO double if check
	if (_pTcpServer == NULL) {
		return _pTcpServer = new TCPServer;
	}
	return _pTcpServer;
}

TCPServer::~TCPServer() {
	if (_Socket.IsConnected())
		_Socket.Close();
}

void TCPServer::Stop() {
	std::cout<<"Stopping TCPServer"<<std::endl;
	connected = false;
	alarm(0);
	if(_ConnectionSocket != NULL)
		if (_ConnectionSocket->IsConnected())
			_ConnectionSocket->Close();
	_isStopped = true;
	std::cout<<"Connection Socket Closed"<<std::endl;
}

void TCPServer::setNetworkAddress(const NetAddress& add_) {
	_netAddr = add_;
}

Header TCPServer::processHeader(const unsigned char* buffer) const {
	Header head;
	memcpy(&head, buffer, HEADER_SIZE);
	UINT16 value = Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("HEADER_DELIMETER", hexadecimal);
	assert(head.start_delimiter == value);
	return head;
}

void TCPServer::InterpretBuffer(const unsigned char *buffer,
		const Header &header, UINT32 size) {
	string xml((char*) buffer);

	UINT32 index = xml.find_last_of('>');

	if((index != std::string::npos) && (index < xml.length()))
		xml = xml.substr(0,index+1);

	std::cout << xml << std::endl;
	::std::istringstream iss(xml, istringstream::binary | istringstream::trunc);
	std::vector<CommandMessage> cmdList;
	std::vector<CommandMessage>::iterator it;
	try {

		switch (header.identifier) {
		case EN_MSG_CMD:

			cmdList = CommandFactory::ParseStream(iss);
			it = cmdList.begin();

			while (it != cmdList.end()) {
				CmdType cmdType = it->GetField(
						&CmdMessageField::tMsgParameters::Command);
				if (cmdType == READ) {
					NotifyListeners(
							ReadEvent(
									it->GetField(
											&CmdMessageField::tMsgParameters::Address),
									it->GetField(
											&CmdMessageField::tMsgParameters::Alignment)));
				} else if (cmdType == WRITE) {
					NotifyListeners(
							WriteEvent(
									it->GetField(
											&CmdMessageField::tMsgParameters::Address),
									it->GetField(
											&CmdMessageField::tMsgParameters::Data),
									it->GetField(
											&CmdMessageField::tMsgParameters::Alignment)));
				} else if (cmdType == CONFIG) {
					ConfigStruct conf;

					conf._RamSize = it->GetField(
							&CmdMessageField::tMsgParameters::RamSize);
					conf._arbiteredIO = it->GetField(
							&CmdMessageField::tMsgParameters::Arbitered_IO);
					conf._baseAddress = it->GetField(
							&CmdMessageField::tMsgParameters::BaseAddress);
					conf._board = it->GetField(
							&CmdMessageField::tMsgParameters::Board);
					conf._device = it->GetField(
							&CmdMessageField::tMsgParameters::Component);
					conf._directIO = it->GetField(
							&CmdMessageField::tMsgParameters::Direct_IO);
					conf._restartHS = it->GetField(
							&CmdMessageField::tMsgParameters::Restart_HS);
					conf._interface = it->GetField(
							&CmdMessageField::tMsgParameters::Interface);
					conf._rtAddress = it->GetField(
							&CmdMessageField::tMsgParameters::RT_Address);
					conf._bitHistoryAddr = it->GetField(
							&CmdMessageField::tMsgParameters::BIT_History_Addr);
					conf._bitHistorySize= it->GetField(
							&CmdMessageField::tMsgParameters::BIT_History_Size);

					//if in Idle then change state to Active
					if (BoardControllerIdle::instance()->GetContext()->GetCurrentState()
							== BoardControllerIdle::instance())
						//BoardControllerIdle::instance()->GetContext()->Handle(ActiveEvent(conf._board ));
						NotifyListeners(ActiveEvent(conf._board));

					//BoardControllerIdle::instance()->GetContext()->Handle((ConfigEvent(conf)));
					NotifyListeners(ConfigEvent(conf));
				} else if (cmdType == TEST) {
					TestStruct test;
					test._channel = it->GetField(
							&CmdMessageField::tMsgParameters::Channel);
					test._configId =
							it->GetField(
									&CmdMessageField::tMsgParameters::ConfigurationType);
					test._step = it->GetField(
							&CmdMessageField::tMsgParameters::StepNumber);
					test._rci = it->GetField(
							&CmdMessageField::tMsgParameters::StepNumber);
					test._terminalNumber = it->GetField(
							&CmdMessageField::tMsgParameters::RT_Address);
					test._testNumber = it->GetField(
							&CmdMessageField::tMsgParameters::TestNumber);
					NotifyListeners(TestsReqEvent(test));
				} else if (cmdType == SGA){
					NotifyListeners(SGA_Event(it->GetField(
							&CmdMessageField::tMsgParameters::SGA)));
				}
				++it;
			}

			cmdList.clear();
			break;
		}
	} catch (xml_schema::exception& ex) {
		throw &ex;
	}
}

void TCPServer::Handle(const CommandResultEvent &event) {
	if (!connected || _isStopped)
		return;
	Logger::getLogger()->Log(DEBUG_LEVEL, "Handle Command Result Event");
	CmdResult res;
	res.SetField(&CmdResultField::tMsgParameters::Result,
			event._cmdResult.Result);
	res.SetField(&CmdResultField::tMsgParameters::CurrentStep,
			event._cmdResult.CurrentStep);
	res.SetField(&CmdResultField::tMsgParameters::IsTerminated,
			(int) event._cmdResult.IsTerminated);
	if(event._cmdResult.ErrorStr[0] != '\0'){
		res.SetMemory<char>((&CmdResultField::tMsgParameters::Message),MAX_BUF_SIZE);
		res.SetArray((&CmdResultField::tMsgParameters::Message),event._cmdResult.ErrorStr,MAX_BUF_SIZE);
	}
	std::string body = CommandResultFactory::CreateCmdResultXML(res);

	//Remove unuseful characters like \n\n
	body = Utils::OptimizeXmlMessage(body);

	if (SendMessage(EN_MSG_CMD_RESULT, body.c_str(), body.length()) < 0)
		NotifyListeners(ErrorEvent());
}

int TCPServer::SendMessage(const EN_MSG_IDENTFIER &id, const char* body, const int &size) {
	if (!connected || _isStopped)
		return -1;
	Logger::getLogger()->Log(DEBUG_LEVEL, "Send Message %d", id);
	std::vector<char> message;
	message = TCPFactoryMessage::CreateTcpMessage(id, body, size);
	char* buffer = new char[message.size()];
	memset(buffer,0,message.size());
	for (UINT32 i = 0; i < message.size(); ++i)
		buffer[i] = message[i];
	int bytes = _ConnectionSocket->Write((UINT8*) buffer, message.size());
	delete[] buffer;
	return bytes;
}

void* TCPServer::run() {

	bool bind = false;
	bool listen = false;
//	int current_size = 0;
	int read_size = 0;

	Logger::getLogger()->Log(INFO_LEVEL, "Server TCP Started");

	bind = _Socket.Bind(_netAddr);
	listen = bind && _Socket.Listen();

	if (!listen) {
		Logger::getLogger()->Log(ERROR_LEVEL, "Server TCP On Error");
		_Socket.Close();
		NotifyListeners(ErrorEvent());
		return NULL;
	}

	//La versione attuale del server accetta una solo connessione per volta
	while (!_isStopped) {
		_ConnectionSocket = _Socket.Accept();
		connected = listen && (_ConnectionSocket != 0);
		this->Sleep(1000);
		while (connected) {

			//READ HEADER
			Logger::getLogger()->Log(INFO_LEVEL, "Server TCP Connected");
			read_size = _ConnectionSocket->Read(_Header, HEADER_SIZE);

			if (read_size <= 0) {
				//Errore in lettore o connessione chiusa prematuramente
				std::cout << "Server TCP Disconnected during header read" << std::endl;
				connected = false;
			} else {
				//Parsing dell'header
				Header header = processHeader(_Header);
				//Read BODY
				_Buffer = new unsigned char[header.msg_size + 1];
				memset(_Buffer,0,header.msg_size + 1);
				read_size = _ConnectionSocket->Read(_Buffer, header.msg_size);
				if (read_size > 0 && ((UINT32)read_size == header.msg_size)) {
					try {
						InterpretBuffer(_Buffer, header, read_size);
					} catch (...) {
						//Buffer non riconosciuto
						//connected = false;
						Logger::getLogger()->Log(DEBUG_LEVEL, "Unknown Message Received");
						delete[] _Buffer;
					}
					delete[] _Buffer;
				} else{
					Logger::getLogger()->Log(DEBUG_LEVEL, "Server TCP Disconnected during body read");
					connected = false;
				}
			}
			//Reset header
			memset(_Header, 0, HEADER_SIZE);
		}
		NotifyListeners(IdleEvent());
	}
	std::cout<<"TCPServer Stopped"<<std::endl;
	return 0;
}

