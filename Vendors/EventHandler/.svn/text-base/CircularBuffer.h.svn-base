#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

class CircularBuffer {
private:
	int _Size;
	char * _Buffer;
	int _ReadIndex;
	int _WriteIndex;

public:
	CircularBuffer(int size);
	~CircularBuffer();

	void Consume(int size);
	void Reset();
	int Put(const char * buffer, int size);
	int Read(char * buffer, int size);
	char operator[](int index) const;

};

#endif
