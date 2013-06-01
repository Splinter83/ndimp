/*
 * XmlLogDevice.cpp
 *
 *  Created on: 06/set/2012
 *      Author: grande
 */

#include "XmlLogDevice.h"
#include "Log.hxx"
#include "ILogger.h"
#include "TCPClient.h"
#include "Utils.h"
#include <cassert>

#include <iostream>
#include <sstream>
#include <string>

XmlLogDevice::XmlLogDevice(){
	_map[""].name = "";
	_map[""].schema = XSD_PATH_NAME "Log.xsd";

//	assert( Utils::isFile( XSD_PATH_NAME "Log.xsd") );

}

XmlLogDevice::XmlLogDevice(const NetAddress& address){
	// TODO Auto-generated constructor stub
	_map[""].name = "";
	_map[""].schema = XSD_PATH_NAME "Log.xsd";

	TCPClient::instance()->SetNetAddress(address);
}

XmlLogDevice::~XmlLogDevice() {
	//TCPClient::instance()->Disconnect();
}


void XmlLogDevice::Close(){
	//TCPClient::instance()->Disconnect();
}

bool XmlLogDevice::Open(){
	return true;//TCPClient::instance()->Connect();
}

/*!
 * Write a string on Ethernet using format described in Log.xsd
 * @param buffer String to write
 * @param size String size
 * @return Buffer size written on stdout
 */
int XmlLogDevice::Write(const char * buffer, int size){
	int bytes = 0;
	const int SPACE_SIZE = 1;
	const int HEADER_SIZE = sizeof(Header);

#ifdef WIN32
    char *locBuffer = new char[size+1];
#else
	char locBuffer [size+1];
#endif
	memset(locBuffer,0,size+1);
	memcpy(locBuffer, buffer, size);

	std::string str(locBuffer);
	UINT32 found = 0;
	std::string value = "";

	/*Parsing della string per inserire nel XML il tipo di log*/

	if((found = str.find(LOG_LEVEL_STRING[INFO_LEVEL])) != std::string::npos){
		value += "INFO";
		str = str.substr(found + strlen(LOG_LEVEL_STRING[INFO_LEVEL]) + SPACE_SIZE, str.length());
	}
	else if((found = str.find(LOG_LEVEL_STRING[ERROR_LEVEL])) != std::string::npos){
		value += "ERROR";
		str = str.substr(found + strlen(LOG_LEVEL_STRING[ERROR_LEVEL]) + SPACE_SIZE, str.length());
	}
	else if((found = str.find(LOG_LEVEL_STRING[WARNING_LEVEL])) != std::string::npos){
		value += "WARN";
		str = str.substr(found + strlen(LOG_LEVEL_STRING[WARNING_LEVEL]) + SPACE_SIZE, str.length());
	}
	else if((found = str.find(LOG_LEVEL_STRING[DEBUG_LEVEL])) != std::string::npos){
		value += "DEBUG";
		str = str.substr(found + strlen(LOG_LEVEL_STRING[DEBUG_LEVEL]) + SPACE_SIZE, str.length());
	}

	/*Settaggio del messaggio*/
	cs::LogType logXml(str);
	/*Settaggio del tipo*/
	logXml.LogLevel().set(value.c_str());
	cs::LogList logListXml(logXml);

	/* oss conterra la stringa xml da inviare su ethernet*/
	std::ostringstream *oss = new std::ostringstream(std::ostringstream::out);
	cs::LogList_(*(static_cast<std::ostream*>(oss)),logListXml,_map);

	std::string body = oss->str();
	body = Utils::OptimizeXmlMessage(body);

	TCPClient::instance()->IsConnected();
		bytes = TCPClient::instance()->Send(LogMsg(body.c_str(),body.length()));

	delete oss;

	return bytes;
}

