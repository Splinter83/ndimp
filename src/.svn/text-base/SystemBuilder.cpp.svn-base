/*
 * SystemBuilder.cpp
 *
 *  Created on: 04/lug/2012
 *      Author: emanuele_galli
 */

#include "SystemBuilder.h"
#include "NetAddress.h"
#include "TCPServer.h"
#include "STIMP.h"
#include "SIMP.h"
#include "OptimizedRefined.h"
#include "OptimizedVmeAdapter.h"
#include "global_definitions.h"
#include "Logger.h"
#include "DataRecorder.h"
#include "DataRecLogger.h"
#include "FilestreamDevice.h"
#include "BoardControllerContext.h"
#include "BoardControllerActiveContext.h"
#include "TCPClient.h"
#include "Singleton.h"
#include "ConfigFile.h"

#ifdef DEBUG
#include "RWTestVmeAdapter.h"
#else
#include "RWTestVmeAdapter.h"
#endif

SystemBuilder::SystemBuilder() :
	//_pLogger(NULL),
    _pTcpServer(NULL),
    _pBoardContext(NULL),
    _pBoardActiveContext(NULL),
    _pTcpClient(NULL)
{


}

SystemBuilder::~SystemBuilder() {
	// TODO Auto-generated destructor stub
	delete _pBoardActiveContext;
	delete _pBoardContext;
	_pBoardActiveContext = NULL;
	_pBoardContext = NULL;
}

void Build(){

}



void SystemBuilder::BuildParts(){
	//_pLogger = CreateLogger();

	_pTcpServer = CreateTcpServer();
	_pTcpServer->setNetworkAddress(NetAddress(
			Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<std::string>("SERVER_ADDRESS", none).c_str()));
	_pBoardActiveContext = CreateBoardControllerContext();
	_pTcpClient = CreateTcpClient();
	_pTcpClient->SetNetAddress(NetAddress(
			Singleton<ConfigFile,CreateThreadSafe>::instance()->getParameter<std::string>("CLIENT_ADDRESS", none).c_str()));
}

void SystemBuilder::CreateLinks(){
	_pTcpServer->AddListeners(_pBoardActiveContext);
	_pBoardActiveContext->AddListeners(_pTcpServer);
}

void SystemBuilder::Start(){
	_pTcpServer->Start();
	_pTcpClient->Start();
	//_pTcpClient->Connect();
	_pBoardActiveContext->Start();
	Logger::getLogger()->Log(DEBUG_LEVEL,"System Builder Started");
}

void SystemBuilder::Stop(){
	_pTcpServer->Stop();
	Logger::getLogger()->Log(DEBUG_LEVEL,"TCP Server Stopped");
	_pBoardActiveContext->Stop();
	Logger::getLogger()->Log(DEBUG_LEVEL,"Board controller Stopped");
	_pTcpClient->Stop();
	Logger::getLogger()->Log(DEBUG_LEVEL,"Tcp Client Stopped");
}

TCPServer* SystemBuilder::CreateTcpServer(){
	return TCPServer::getTcpServer();
}

TCPClient*  SystemBuilder::CreateTcpClient(){
	return TCPClient::instance();
}

/*Logger* SystemBuilder::CreateLogger(){

#ifdef DEBUG
	Logger::getLogger()->EnableLogLevel(DEFAULT_LEVEL);
#endif
	Logger::getLogger()->EnableLogLevel(DEBUG_LEVEL);
	Logger::getLogger()->EnableLogLevel(WARNING_LEVEL);
	Logger::getLogger()->EnableLogLevel(ERROR_LEVEL);
	Logger::getLogger()->EnableLogLevel(FATAL_LEVEL);
	Logger::getLogger()->EnableLogLevel(INFO_LEVEL);
	return Logger::getLogger();
}*/

BoardControllerActiveContext* SystemBuilder::CreateBoardControllerContext(){
	this->_pBoardContext = new BoardControllerContext;
	return new BoardControllerActiveContext(this->_pBoardContext);
}

