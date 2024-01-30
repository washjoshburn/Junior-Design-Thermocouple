#include "xc.h"
#include "farru049_circularBuff_v001.h"

void initBuffer(void){
    for(int i = 0; i < BUFFERSIZE; i++){
        buffer[i] = 0;
    }
}

void putVal(int newVal){
    buffer[buffIndex] = newVal;
    buffIndex = (buffIndex + 1) % BUFFERSIZE;
}

int getAvg(void){
    unsigned long int sum = 0;
    
    for(int i = 0; i < BUFFERSIZE; i++){
        sum += buffer[i];
    }
    return sum/BUFFERSIZE;
}