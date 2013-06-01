/*
 * main.cpp
 *
 *  Created on: 30/mag/2012
 *      Author: emanuele_galli
 */


//#define LOG_FILE
//#define DEBUG
#define LOG_CONSOLE

#include <iostream>
#include "Logger.h"
#include "ConsoleDevice.h"
#include "FilestreamDevice.h"
#include "XmlLogDevice.h"
#include "DataRecorder.h"
#include "DataRecLogger.h"
#include <unistd.h>
#include "SystemBuilder.h"
#include "Singleton.h"
#include "ConfigFile.h"

#include <signal.h>
#include <xercesc/util/PlatformUtils.hpp>

SystemBuilder* builder;
extern bool isSystemStopped;

void signal_callback_handler(int signum){
	isSystemStopped = true;
}

int main(int argc, char** argv) {

//ConfigFile
Singleton<ConfigFile, CreateThreadSafe>::instance()->load("config");

#ifdef LOG_CONSOLE
    ConsoleDevice record_device;
#elif  defined(LOG_FILE)
    FilestreamDevice record_device;
#else
    XmlLogDevice record_device;
#endif

    signal(SIGINT, signal_callback_handler);
    signal(SIGQUIT, signal_callback_handler);
    signal(SIGABRT, signal_callback_handler);

    xercesc::XMLPlatformUtils::Initialize ();

	DataRecorder data_rec;
	data_rec.SetDevice(&record_device);
	DataRecLogger rec_logger(&data_rec);


	Logger::getLogger()->setLogger(&rec_logger);

#ifdef DEBUG
	Logger::getLogger()->EnableLogLevel(DEBUG_LEVEL);
#endif
	Logger::getLogger()->EnableLogLevel(DEFAULT_LEVEL);
	Logger::getLogger()->EnableLogLevel(WARNING_LEVEL);
	Logger::getLogger()->EnableLogLevel(ERROR_LEVEL);
	Logger::getLogger()->EnableLogLevel(FATAL_LEVEL);
	Logger::getLogger()->EnableLogLevel(INFO_LEVEL);

	sleep(1);

	builder = new SystemBuilder();
	builder->BuildParts();
	builder->CreateLinks();
	builder->Start();

	while(!isSystemStopped){
		sleep(1);
	}

	std::cout << "System is going to stop..." << std::endl;

    builder->Stop();

    std::cout << "System stopped" << std::endl;

    xercesc::XMLPlatformUtils::Terminate ();

	return (0);
}

