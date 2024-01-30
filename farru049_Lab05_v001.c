/*
 * File:   farru049_Lab05_v001.c
 * Author: stone
 *
 * Created on July 12, 2023, 12:09 PM
 */


#include "xc.h"
#include "farru049_Lab05_mainLib_v001.h"

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

#define RIGHT 1
#define LEFT 0


void setup(void)
{
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0xffff;            //sets all pins to digital I/O

      
    lcd_init();
}


void loop(void){
    lcd_setCursor(0,0);
    lcd_printStr("Hello");
    lcd_setCursor(1, 0);
    lcd_printStr("World!");
    lcd_shift(RIGHT);
    delay(500);
}

void animate(void){
    char string[] = {'H', 'e', 'l','l','o', ' ', 'W', 'o','r','l','d','!','\0'};
    int x_line = 0;
    int y_line = 0;
    for(int i = 0; i < 13; i++){
        if((y_line == 7)||(string[i] == ' ')){
            y_line = 0; 
            x_line = 1;
        }
        lcd_setCursor(x_line, y_line);
        lcd_printChar(string[i]);
        y_line++;

        delay(1000);
    }
}


int main(void) {
    setup();

    //animate();
    while(1){
        loop();
    }
    return 0;
}
