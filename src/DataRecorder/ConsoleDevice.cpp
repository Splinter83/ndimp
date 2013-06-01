/*
 * ConsoleDevice.cpp
 *
 *  Created on: 06/giu/2012
 *      Author: emanuele_galli
 */

#include "ConsoleDevice.h"

#include <stdio.h>
#include <string.h>

#include <iostream>

ConsoleDevice::ConsoleDevice() {
	// TODO Auto-generated constructor stub

}

ConsoleDevice::~ConsoleDevice() {
	// TODO Auto-generated destructor stub
}

void ConsoleDevice::Close() {

}

bool ConsoleDevice::Open() {
	return true;
}

int ConsoleDevice::Write(const char * buffer, int size) {
    //#[ operation Write(const char *,int)
    // qui il console device prende in carico i dati
#ifdef WIN32
    char *locBuffer = new char[size+1];
#else
//	char locBuffer [size+1];
    char *locBuffer = new char[size+1];
#endif
	memcpy(locBuffer, buffer, size);
	// termina stringa
	locBuffer[size] = 0;
	std::cout << locBuffer << std::endl;
    // come feedback restituisce la dimensione dell'ultimo messaggio ricevuto
#ifdef WIN32
	delete []locBuffer;
#else
	delete []locBuffer;
#endif
    return(size);
    //#]
}
