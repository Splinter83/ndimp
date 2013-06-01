#include "CircularBuffer.h"
#include <algorithm>
CircularBuffer::CircularBuffer(int size) :
		_Size(size), _Buffer(new char[_Size]), _ReadIndex(0), _WriteIndex(0) {
	std::fill(_Buffer, &_Buffer[_Size], 0);
}

CircularBuffer::~CircularBuffer() {
	delete[] _Buffer;
}

void CircularBuffer::Reset() {
	_ReadIndex = _WriteIndex = 0;
	std::fill(_Buffer, &_Buffer[_Size], 0);
}

int CircularBuffer::Put(const char * buffer, int size) {
	// Lock
	int result = size;

	if (_WriteIndex >= _ReadIndex) {
		if (_WriteIndex + size < _Size)
			std::copy(buffer, buffer + size, &_Buffer[_WriteIndex]);
		else if ((_WriteIndex + size >= _Size) && (_ReadIndex == 0)) {
			result = _Size - _WriteIndex - 1;
			if (result)
				std::copy(buffer, buffer + result, &_Buffer[_WriteIndex]);
		} else {
			int size1 = _Size - _WriteIndex;
			std::copy(buffer, buffer + size1, &_Buffer[_WriteIndex]);

			int size2 = (
					_ReadIndex - 1 < (size - size1) ?
							_ReadIndex - 1 : size - size1);
			std::copy(&buffer[size1], &buffer[size1 + size2], &_Buffer[0]);
			result = size1 + size2;
		}
	} else {
		result = (
				size < (_ReadIndex - _WriteIndex) ?
						size : _ReadIndex - _WriteIndex);
		std::copy(buffer, buffer + result, &_Buffer[_WriteIndex]);
	}

	_WriteIndex = (_WriteIndex + result) % _Size;

	return result;
}

int CircularBuffer::Read(char * buffer, int size) {
	//Lock
	int result = size;

	if (_ReadIndex == _WriteIndex)
		result = 0;

	else if (_ReadIndex > _WriteIndex) {
		if (_ReadIndex + size < _Size)
			std::copy(&_Buffer[_ReadIndex], &_Buffer[_ReadIndex] + size,
					buffer);
		else {
			int size1 = _Size - _ReadIndex;
			std::copy(&_Buffer[_ReadIndex], &_Buffer[_ReadIndex] + size1,
					buffer);

			int size2 = (
					_WriteIndex < (size - size1) ? _WriteIndex : size - size1);
			std::copy(&_Buffer[0], &_Buffer[size2], &buffer[size1]);
			result = size1 + size2;
		}
	} else {
		result = (
				size < (_WriteIndex - _ReadIndex) ?
						size : _WriteIndex - _ReadIndex);
		std::copy(&_Buffer[_ReadIndex], &_Buffer[_ReadIndex] + result, buffer);

	}

	//_ReadIndex=(_ReadIndex+result)%_Size;
	return result;
}

char CircularBuffer::operator[](int index) const {
	//Lock
	int idx = (index + _ReadIndex) % _Size;

	return _Buffer[idx];
}

void CircularBuffer::Consume(int size) {
	//Lock
	_ReadIndex = (_ReadIndex + size) % _Size;
}

