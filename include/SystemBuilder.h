/*
 * SystemBuilder.h
 *
 *  Created on: 04/lug/2012
 *      Author: emanuele_galli
 */

#ifndef SYSTEMBUILDER_H_
#define SYSTEMBUILDER_H_


class TCPServer;
class TCPClient;
//class Logger;
class BoardControllerContext;
class BoardControllerActiveContext;

class SystemBuilder {
public:
	SystemBuilder();
	virtual ~SystemBuilder();

	void BuildParts();
	void CreateLinks();
	void Start();

	void Stop();

protected:
	TCPServer* CreateTcpServer();
	TCPClient*  CreateTcpClient();
	//Logger* CreateLogger();
	BoardControllerActiveContext* CreateBoardControllerContext();

protected:
	TCPServer* _pTcpServer;
	TCPClient* _pTcpClient;
	//Logger* _pLogger;
	BoardControllerContext* _pBoardContext;
	BoardControllerActiveContext* _pBoardActiveContext;
};

#endif /* SYSTEMBUILDER_H_ */
