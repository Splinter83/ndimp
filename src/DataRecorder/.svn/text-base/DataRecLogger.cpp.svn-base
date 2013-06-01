/*
 * DataRecLogger.cpp
 *
 *  Created on: 05/giu/2012
 *      Author: emanuele_galli
 */

#include "DataRecLogger.h"
#include "DataRecorder.h"
#include "RecordableItem.h"
#include <string>
#include <stdio.h>
#include <cstring>

DataRecLogger::DataRecLogger(DataRecorder *dataRec) {
	_pDataRecorder = dataRec;

}

DataRecLogger::~DataRecLogger() {
}

void DataRecLogger::Log(UINT8 level, const char * logmsg) {
	if (IsLevelEnabled(level)) {

		struct tm * timeinfo;
		time_t rawtime;
		char time_buffer[30];
		char buffer[MAX_BUF_SIZE];
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		strftime (time_buffer,MAX_BUF_SIZE,"[%x %X] ",timeinfo);
		sprintf(buffer,"%s %s %s",time_buffer,LOG_LEVEL_STRING[level],logmsg);

		//strcat(buffer,LOG_LEVEL_STRING[level]);
		//strcat(buffer,logmsg)

		// crea un Recordable Item per fornirlo in input al Data Recorder
		RecordableItem *recItem = new RecordableItem();
		// inserisce nel buffer del Recordable Item il dato da stampare
		// questo oggetto verrà distrutto dopo l'utilizzo del Data Recorder
		// una volta estratto dalla coda
		if (recItem) {
			recItem->SetBuffer(buffer, strlen(buffer));
			// inserisce l'oggetto recordable nella coda del Data Recorder
			int res = _pDataRecorder->Write(recItem);
			if (!res) {
				//in tutti i casi de-alloco
				delete recItem;
				printf("DataRecorder:Loss of Data.....QUEUE FULL!\n");
			}
		}
	}
}

