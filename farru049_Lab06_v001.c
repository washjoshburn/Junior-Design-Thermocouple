/*
 * File:   farru049_Lab06_v001.c
 * Author: stone
 *
 * Created on July 19, 2023, 12:45 PM
 */


#include "xc.h"
#include "farru049_circularBuff_v001.h"
#include "farru049_Lab05_mainLib_v001.h"
#include <stdio.h>

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


void __attribute__((__interrupt__,__auto_psv__))_ADC1Interrupt(void){
    IFS0bits.AD1IF = 0;
    
    int valADC = ADC1BUF0;
    putVal(valADC);
}


void setup(void){
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9ffe; //all digital inputs and outputs
    TRISA |= 1;
    
    TMR3 = 0;
    T3CON = 0;
    _T3IF = 0;
    T3CONbits.TCKPS = 0b10;
    PR3 = 15624;
    T3CONbits.TON = 1;
    
   
    AD1CON2bits.VCFG = 0b000;
    AD1CON1bits.SSRC = 0b010;  //Rollover to conversion
    AD1CON1bits.ASAM = 1; // auto-sample
    AD1CON1bits.FORM = 0b00;
    AD1CON2bits.SMPI = 0b0; // every conversion
    AD1CON3bits.ADCS = 0b1;
    AD1CON3bits.SAMC = 0b10;
    AD1CON1bits.ADON = 1; // ton


    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 1;   
}

int main(void) {
    setup();
    initBuffer();
    lcd_init();
    
    
    char avgStr[20];
    while(1){
        while(!_T3IF);
        _T3IF = 0;
        //unsigned int average = getAvg();
        sprintf(avgStr, "%6.4f C", (3.3/1024)*ADC1BUF0);
        lcd_setCursor(0, 0);
        lcd_printStr(avgStr);
        
        delay(500);
        
    }
    return 0;
}
