#ifndef IOutputDataStream_H
#define IOutputDataStream_H


#include <string>

#include <algorithm>



    class IOutputDataStream {

    public :

        IOutputDataStream();

        inline virtual ~IOutputDataStream() {}

        virtual int Write(const char * buffer, int size) = 0;
    };

#endif
