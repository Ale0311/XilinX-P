

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Channel.h"
#include "Data.h"

using namespace ::std;

BSC::BSC(unsigned p) {
    
    this->p = p;

}

BSC::~BSC() {
    // TODO Auto-generated destructor stub
}

Data* BSC::applyChannel(Data *coded_vector, unsigned dataLength) {
    
    
    int i;
    srand(time(NULL));
    
    //values before
    
    for ( i=0;i<dataLength;i++) cout << coded_vector[i].getValue();
    cout <<endl;
    
    Data flipBit;
    flipBit.setValue(1);
    
    int bitsFlippedCounter=0;
    
    for ( i=0;i<dataLength;i++){
        int newProbability =rand()%100 + 1;
        if ( newProbability <= this->p ){
            coded_vector[i] = coded_vector[i] + flipBit;
            bitsFlippedCounter ++;
        }
        
        
        
    }
    
    for ( i=0;i<dataLength;i++) cout << coded_vector[i].getValue();
    cout<<endl<<bitsFlippedCounter<<" bits flipped after aplying this channel"<<endl;
    
    return coded_vector;
}


int main () {
    
    Data *testVector;
    testVector=(Data *)calloc(100, sizeof(Data));
    
    
    //testVector[2].setValue(1);
    //testVector[4].setValue(1);
    
    
    BSC binaryChannel(30);
    binaryChannel.applyChannel(testVector,100);
}
