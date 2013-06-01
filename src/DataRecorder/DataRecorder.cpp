/*
 * DataRecorder.cpp
 *
 *  Created on: 05/giu/2012
 *      Author: emanuele_galli
 */

#include "DataRecorder.h"
#include "IRecordingDevice.h"
#include "IRecordable.h"
#include "MutextCondition.h"

#include <iostream>

#include <string.h>

struct producerArg{
	std::vector<IRecordable*> *queueArg;
	IRecordable* recordable;
};

struct consumerArg{
	std::vector<IRecordable*> *queueArg;
	IRecordingDevice *device;
};

#define MAX_BUF_SIZE 1024

DataRecorder::DataRecorder(IRecordingDevice *device) :
		_thread(
				new Thread(auto_ptr<Runnable>(this))) {

	//itsIRecordingDevice = device;
	_pMutex = new Mutex;
	pCondition = new MutexCondition(_pMutex);
	_thread->start();
	std::cout << "DataRecoredThread Started."<<std::endl;
}

DataRecorder::~DataRecorder() {
	//All external call are soon disabled
	_isStopped = true;
	//Write all messages
	while (_queue.size() > 0) {
		char buffer[MAX_BUF_SIZE];
		IRecordable *recordable = _queue.back();
		_queue.pop_back();

		int size;
		do {
			size = recordable->Read(buffer, MAX_BUF_SIZE);
			if (itsIRecordingDevice && size)
				itsIRecordingDevice->Write(buffer, size);
			memset(buffer, 0, MAX_BUF_SIZE);
		} while (size == MAX_BUF_SIZE);

		delete recordable;
	}
	//Kill Thread
	pCondition->Signal();
	delete pCondition;
	delete _pMutex;
}

void DataRecorder::SetDevice(IRecordingDevice * device) {
	itsIRecordingDevice = device;
}

void* DataRecorder::produce(void* arg) {
	//Inserisce nella coda dei messaggi uno nuovo
	producerArg* prod = static_cast<producerArg*>(arg);
	prod->queueArg->push_back(prod->recordable);
	return NULL;
}

void* DataRecorder::consume(void *arg) {
	//Legge e scrive un messaggio presente in coda e lo rimuove da quest'ultima
	char buffer[MAX_BUF_SIZE];
	consumerArg* cons = static_cast<consumerArg*>(arg);
	if (cons->queueArg->size() > 0) {
		//prende l'ultimo messaggio ricevuto
		IRecordable *recordable = cons->queueArg->back();
		//rimozione messaggio dalla coda
		cons->queueArg->pop_back();
		int size;
		//Write all data on device
		do {
			size = recordable->Read(buffer, MAX_BUF_SIZE);
			if (cons->device && (size > 0))
				//scrittura messaggio sul device
				if(cons->device->Write(buffer, size) < 0){
					return NULL;
				}
				else{
					return false;
				}
			memset(buffer, 0, MAX_BUF_SIZE);
		} while (size == MAX_BUF_SIZE);
		delete recordable;
	}
	return NULL;
}

bool DataRecorder::Write(IRecordable * recordable) {
	//Il messaggio viene aggiunto in coda
	producerArg arg;
	arg.queueArg = &_queue;
	arg.recordable = recordable;
	if(_isStopped)
		return false;
	//La funzione produce viene eseguita prima di lanciare il segnale
	// Con il segnale viene svegliato il thread in attesa di un nuovo messaggio
	pCondition->Signal(&(DataRecorder::produce), (void*)&arg);
	return true;
}

void* DataRecorder::run() {
	consumerArg arg;
	arg.device = itsIRecordingDevice;
	arg.queueArg = &_queue;

	itsIRecordingDevice->Open();

	_isStopped = false;
	std::cout<< "Device is open" << std::endl;

	while (!_isStopped) {
		//Si mette in attesa di ricevere un nuovo messaggio. La funzione consume viene eseguito dopo la ricezione del segnale
		pCondition->Wait(&(DataRecorder::consume), (void*)&arg);

		/*TODO
		* Controllare che la scrittura sia andata bene o almeno che il device sia in uno stato consistente
		*/
	}
	std::cout<< "Device shutdown" << std::endl;
	itsIRecordingDevice->Close();
	std::cout<< "Device closed" << std::endl;
	return 0;
}

