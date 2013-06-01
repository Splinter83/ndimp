/*
 * RecordableItem.cpp
 *
 *  Created on: 05/giu/2012
 *      Author: emanuele_galli
 */

#include "RecordableItem.h"
#include <string.h>

RecordableItem::RecordableItem(int MaxBufferSize) {
	_plocalBuffer = new char[MaxBufferSize];
	_localBufferSize = MaxBufferSize;
	_availableDataSize = 0;

}

RecordableItem::~RecordableItem() {
	delete[] _plocalBuffer;
}

int RecordableItem::Read(char* buffer, int size) {
	int transferDataSize =
			(_availableDataSize > size) ? size : _availableDataSize;
	// copia i dati con la dimensione richiesta (quelli disponibili fino ad un max di size)
	memcpy(buffer, _plocalBuffer, transferDataSize);
	// se il buffer richiesto è minore di quello disponibile
	if (_availableDataSize > transferDataSize) {
		// al prossimo read i dati disponibili saranno di meno
		_availableDataSize -= transferDataSize;
		// trasla il buffer dei dati, quelli già copiati vengono sovrascritti
		// quindi l'array partirà (elemento 0) sempre dai dati ancora da trasferire
		memcpy(_plocalBuffer, _plocalBuffer + transferDataSize,
				_availableDataSize - transferDataSize);
	} else {
		_availableDataSize = 0; // per pulizia imposta a 0 i dati disponibili
	}
	return (transferDataSize);
}

int RecordableItem::SetBuffer(const char * bufferIn, int sizeIn) {
	int minSize = (sizeIn > _localBufferSize) ? _localBufferSize : sizeIn;
	memcpy(_plocalBuffer, bufferIn, minSize);
	_availableDataSize = minSize;
	return minSize;
}
