/* 
 * File:   farru049_circularBuff_v001.h
 * Author: stone
 *
 * Created on July 20, 2023, 11:43 AM
 */

#ifndef FARRU049_CIRCULARBUFF_V001_H
#define	FARRU049_CIRCULARBUFF_V001_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define BUFFERSIZE 1024

static int buffer[BUFFERSIZE];
static int buffIndex = 0;

void initBuffer(void);
void putVal(int);
int getAvg(void);


#ifdef	__cplusplus
}
#endif

#endif	/* FARRU049_CIRCULARBUFF_V001_H */

