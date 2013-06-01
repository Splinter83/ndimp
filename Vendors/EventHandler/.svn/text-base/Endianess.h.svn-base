//---------------------------------------------------------------------------

#ifndef EndianessH
#define EndianessH
//---------------------------------------------------------------------------
#include <algorithm>


typedef unsigned char B_OCTET;
// template di utilita' per il cambio della endianess dei tipi base
template <typename T> T changeEndianess(const T & o)
{
	union CharArray {
		T 		data;
		B_OCTET	rawData[sizeof(T)];
	} tmp;

	tmp.data = o;

	const int endOfSwap = sizeof(T)/2;
	int j = sizeof(T) - 1;
	for(int i=0;i<endOfSwap;++i, --j){
		std::swap(tmp.rawData[i], tmp.rawData[j]);
	}
	return tmp.data;
}

template <typename T> void normalyzeEndianess(T & o)
{
    o = changeEndianess(o);
}


#endif
