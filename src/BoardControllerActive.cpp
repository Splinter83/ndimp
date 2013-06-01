/*
 * SimpStimpProject: BoardControllerActive.cpp
 *
 *  Created on: 02/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#include "BoardControllerActive.h"
#include "BoardControllerContext.h"
#include "BoardControllerError.h"
#include "BoardControllerIdle.h"
#include "I_TSAP.h"
#include "I_TEST.h"
#include "SIMP.h"
#include "STIMP.h"
#include "Logger.h"
#include "MessageXml.h"
#include "TsapMessage.h"
#include "DiscreteFactory.h"
#include "GlobalTypes.h"
#include "DiscreteManager.h"
#include "Utils.h"
#include "TCPClient.h"

BoardControllerActive::BoardControllerActive() {
	// TODO Auto-generated constructor stub
	discrete_map[EN_DI_1]  = "DI1";
	discrete_map[EN_DI_2]  = "DI2";
	discrete_map[EN_DI_3]  = "DI3";
	discrete_map[EN_DI_4]  = "DI4";
	discrete_map[EN_DI_5]  = "DI5";
	discrete_map[EN_DI_6]  = "DI6";
	discrete_map[EN_DI_7]  = "DI7";
	discrete_map[EN_DI_8]  = "DI8";
	discrete_map[EN_DI_9]  = "DI9";
	discrete_map[EN_DI_10] = "DI10";
	discrete_map[EN_DI_11] = "DI11";
	discrete_map[EN_DI_12] = "DI12";
	discrete_map[EN_DO_1]  = "DO1";
	discrete_map[EN_DO_2]  = "DO2";
	discrete_map[EN_DO_3]  = "DO3";
	discrete_map[EN_DO_4]  = "DO4";
	discrete_map[EN_DO_5]  = "DO5";
	discrete_map[EN_DO_6]  = "DO6";
	discrete_map[EN_DO_7]  = "DO7";
	discrete_map[EN_DO_8]  = "DO8";
	discrete_map[EN_DO_9]  = "DO9";
	discrete_map[EN_DO_10] = "DO10";
	discrete_map[EN_DO_11] = "DO11";
	discrete_map[EN_DO_12] = "DO12";

	handover_map[EN_HIACT_ALTH] = "HIACT_ALTH";//Handover
	handover_map[EN_HIACT_NLTH] = "HIACT_NLTH";
	handover_map[EN_DEM_ALTH]   = "DEM_ALTH";
	handover_map[EN_DEM_NLTH]   = "DEM_NLTH";
	handover_map[EN_ACT_ALTH]   = "ACT_ALTH";
	handover_map[EN_ACT_NLTH]   = "ACT_NLTH";
	handover_map[EN_LOADM_ALTH] = "LOADM_ALTH";
	handover_map[EN_LODEM_NLTH] = "LODEM_NLTH";

	general_conf_map[0] = "OPT_RESET";
	general_conf_map[1] = "SNOGO";
	general_conf_map[2] = "OVERRIDE";
	general_conf_map[3] = "MNOGO";

	isReadDiscreteActive = false;
}

BoardControllerActive::~BoardControllerActive() {
	// TODO Auto-generated destructor stub
}

void BoardControllerActive::Handle(const OnEntryEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL, "Enter in Active state");
	BoardControllerContext* context =
			dynamic_cast<BoardControllerContext*>(this->GetContext());
	context->getBoardInterafce()->initBoard();
//	if ((dynamic_cast<SIMP*>(context->getBoardInterafce()) != NULL)
//			|| (dynamic_cast<STIMPboard*>(context->getBoardInterafce()) != NULL))
		//DiscreteManager::instance()->Start();

	//Connect Client
	TCPClient::instance()->Connect();

	if(this->_isStopped)
		this->Start();
	isReadDiscreteActive = true;
}

void BoardControllerActive::Handle(const OnExitEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL, "Exit from Active state");
	this->Stop();
	isReadDiscreteActive = false;
	TCPClient::instance()->Disconnect();
	//DiscreteManager::instance()->Stop();
}

void BoardControllerActive::Handle(const IdleEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL, "Idle Event receive in active state");
	ChangeState(BoardControllerIdle::instance());
}

void BoardControllerActive::Handle(const ActiveEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL,
			"Active Event receive in active state");
}

void BoardControllerActive::Handle(const ErrorEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL,
			"Error Event receive in active state");
	ChangeState(BoardControllerError::instance());
}

void BoardControllerActive::Handle(const ShutdownEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL,
			"Shutdown Event receive in active state");
}

void BoardControllerActive::Handle(const SGA_Event & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL, "SGA Event receive in active state");
}

void BoardControllerActive::Handle(const WriteEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL,
			"Write Event receive in active state");

	isReadDiscreteActive = false;

	BoardControllerContext* context =
			dynamic_cast<BoardControllerContext*>(this->GetContext());

	ResultStruct res;
	res.CurrentStep = 1;
	res.IsTerminated = true;
	try {
		context->getBoardInterafce()->write(msg._data, msg._address,
				msg._align);
		res.Result = 0;
		res.CommandSuccess = true;
	} catch (const std::string &err) {
		res.Result = 1;
		res.CommandSuccess = false;
		strcpy(res.ErrorStr, err.c_str());
	}

	isReadDiscreteActive = !isReadDiscreteActive;

	context->NotifyListeners(CommandResultEvent(res));
}

void BoardControllerActive::Handle(const ReadEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL, "Read Event receive in active state");
	BoardControllerContext* context =
			dynamic_cast<BoardControllerContext*>(this->GetContext());
	isReadDiscreteActive = !isReadDiscreteActive;
	ResultStruct res;
	res.CurrentStep = 1;
	res.IsTerminated = true;
	try {
		UINT32 data = context->getBoardInterafce()->read(msg._address,
				msg._align);
		res.Result = data;
		res.CommandSuccess = true;
	} catch (const std::string &err) {
		res.Result = -1;
		res.CommandSuccess = false;
		strcpy(res.ErrorStr, err.c_str());
	}
	isReadDiscreteActive = !isReadDiscreteActive;
	context->NotifyListeners(CommandResultEvent(res));
}

void BoardControllerActive::Handle(const TestsReqEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL,
			"Test Request Event receive in active state");
	BoardControllerContext* context =
			dynamic_cast<BoardControllerContext*>(this->GetContext());
	//isReadDiscreteActive = !isReadDiscreteActive;
	UINT32 ret = TEST_NOK;
	ResultStruct res;
	res.CurrentStep = msg._test._step;

	try {
		ret = context->getBoardInterafce()->execTest(msg._test);
		res.Result = ret;
		if (ret == TEST_OK) {
			res.CommandSuccess = true;
			res.IsTerminated = true;
		} else if (ret == NEXT_STEP) { // A new step has to be executed
			res.IsTerminated = false;
		} else { //On error
			res.CommandSuccess = false;
			res.IsTerminated = true;
			strcpy(res.ErrorStr, context->getBoardInterafce()->getLastError());
		}
	} catch (const std::string &err) {
		res.Result = -1;
		res.CommandSuccess = false;
		strcpy(res.ErrorStr, err.c_str());
	}
	//isReadDiscreteActive = !isReadDiscreteActive;
	context->NotifyListeners(CommandResultEvent(res));
}

void BoardControllerActive::Handle(const ConfigEvent & msg) {
	Logger::getLogger()->Log(DEBUG_LEVEL,
			"Configuration Event receive in active state");
	GlobalData::instance()->AddInterface(msg._config);
	BoardControllerContext* context =
			dynamic_cast<BoardControllerContext*>(this->GetContext());
	context->getBoardInterafce()->setupRemoteTerminal();
}

void BoardControllerActive::Handle(const DiscreteEvent & msg) {

}

void* BoardControllerActive::run() {
	UINT32 discrete = 0;
	UINT32 general_config = 0;
	UINT32 handover = 0;
	UINT8 handover_counter[8] = {0};
	DiscreteStruct discrete_field;
	BasicDiscreteStatusVect discrete_vect;

	BoardControllerContext* context =
			dynamic_cast<BoardControllerContext*>(this->GetContext());

	I_TSAP *boardInterface = context->getBoardInterafce();

	while (!_isStopped) {
		discrete = 0;
		general_config = 0;
		handover = 0;
		while (isReadDiscreteActive) {
			AllDiscreteType read_discrete =
					context->getBoardInterafce()->readAllDiscrete();
			general_config = general_config
					^ read_discrete.general_config_reg.raw32;
			//STIMP
			if (dynamic_cast<STIMPboard*>(boardInterface) != NULL) {
				discrete = discrete ^ read_discrete.discrete_reg.raw32;
				handover = handover ^ read_discrete.handover_reg.raw32;

				bool discIsChanged = false;
				bool generalIsChanged = false;
				bool handoverIsChanged = false;
				for (UINT32 i = 0; i < (discrete_map.size() + handover_map.size()); ++i) {
					discIsChanged = discrete & 0x1; //checks that first bit in current value of discrete is changed

					if (discIsChanged && i < discrete_map.size()) {
						discrete_field.Status =
								((read_discrete.discrete_reg.raw32) >> i) & 0x1;
						discrete_field.SetName(
								(const char*) discrete_map[i].c_str(),
								(discrete_map[i]).length());
						discrete_vect.push_back(discrete_field);
					}

					else if(i <=  EN_HIACT_ALTH && i >= EN_DEM_NLTH){
						handoverIsChanged = handover & 0x1;
						if(handoverIsChanged){
							++handover_counter[i];
							//if((handover_counter[i] % 2) == 0){
								discrete_field.Status =
 											((read_discrete.handover_reg.raw32) >> (i-discrete_map.size())) & 0x1;
								discrete_field.SetName(
											(const char*) handover_map[i].c_str(),
															(handover_map[i]).length());
								discrete_vect.push_back(discrete_field);
							//}
							//else{
							//	handover_counter[i] = 0;
							//}
						}
						handover >>= 1;
					}

					if (i < general_conf_map.size()) {
						generalIsChanged = general_config & 01; //checks that first bit in current value of general config is changed
						if (generalIsChanged) {
							discrete_field.Status =
									((read_discrete.general_config_reg.raw32)
											>> i) & 0x1;
							discrete_field.SetName(
									(const char*) general_conf_map[i].c_str(),
									(general_conf_map[i]).length());
							discrete_vect.push_back(discrete_field);
						}
					}

					discrete >>= 1; //lets check next bit
					general_config >>= 1;
				}

				discrete = read_discrete.discrete_reg.raw32;
				handover = read_discrete.handover_reg.raw32;
				general_config = general_config
						| read_discrete.general_config_reg.raw32;
			}
			//SIMP1 and SIMP2
			else if (dynamic_cast<SIMP*>(boardInterface) != NULL) {
				bool generalIsChanged = false;
				for (UINT32 i = 0; i < general_conf_map.size(); ++i) {
					generalIsChanged = general_config & 01; //checks that first bit in current value of general config is changed
					if (generalIsChanged && i < general_conf_map.size()) {
						discrete_field.Status =
								((read_discrete.general_config_reg.raw32) >> i)
										& 0x1;
						discrete_field.SetName(
								(const char*) general_conf_map[i].c_str(),
								(general_conf_map[i]).length());
						discrete_vect.push_back(discrete_field);
					}
					general_config >>= 1;
				}
				general_config = general_config
						| read_discrete.general_config_reg.raw32;
			}

			if (discrete_vect.size() > 0) {
				std::string body = DiscreteFactory::CreateDiscretetXML(
						discrete_vect);
				body = Utils::OptimizeXmlMessage(body);
				if(TCPClient::instance()->Send(
				DiscreteMsg(body.c_str(), body.length())) <=  0 ){
					general_config = 0;
					discrete = 0;
				}
			}
			discrete_vect.clear();
			this->Sleep(MSEC_TO_USEC(100));
		}
		this->Sleep(MSEC_TO_USEC(500));
	}
	std::cout << "BoardControllerActive Stopped" << std::endl;
	return NULL;
}

