#ifndef CHANNEL_LDPCENCODER_H_
#define CHANNEL_LDPCENCODER_H_

#include<fstream>
#include"Data.h"
#include "Message.h"


class Channel {
public:
    virtual Data* applyChannel(Data *coded_vector,unsigned dataLength)=0; // Pure virtual function makes
                                                                        // this class Abstract class.
};


class BSC
{

public:
    
    float p;
    BSC(float p);
    ~BSC();
    
    Data* applyChannel(Data *coded_vector,unsigned dataLength);
};
  
#endif /* CHANNEL_LDPCENCODER_H_ */
