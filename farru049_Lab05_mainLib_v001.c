#include "xc.h"
#include "farru049_Lab05_mainLib_v001.h"

void lcd_shift(int dir){
    dir = dir << 2;
    char data = 0b00011011 | dir; 
    
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN= 0b01111100;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    
    I2C2TRN= 0b00000000;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    
    I2C2TRN = data; 
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
}

void delay (unsigned int ms){
    while(ms-->0){ 
        asm("repeat #15998"); // asm function delay, format taken from pre-lab video
        asm("nop");
    }
}

void lcd_cmd(char Package){
    // send START message

    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN= 0b01111100;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    
    I2C2TRN= 0b00000000;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    
    I2C2TRN = Package; 
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
}

void lcd_init(void){
    I2C2BRG = 0x9D; //set baud generator to Fscl of 100kHz
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.I2CEN = 1;
    
    delay(40);

    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00111001); // function set, extended instruction mode
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110000); // contrast C3-C0
    lcd_cmd(0b01011110); // Ion, Bon, C5-C4
    lcd_cmd(0b01101100); // follower control
   
    delay(200);
    
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00001100); // Display On
    lcd_cmd(0b00000001); // Clear Display
    
    delay(2);
}
void lcd_setCursor(char x, char y){
    lcd_cmd(((0x40*x)+y)| 0b10000000);
}

void lcd_printChar(char myChar){
        // send START message
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN==1);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN= 0b01111100;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    
    I2C2TRN= 0b01000000;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    
    I2C2TRN = myChar; 
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
}

void lcd_printStr(const char *s) {
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;

    I2C2TRN = 0b01111100;
    while (!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;

    I2C2TRN = 0b11000000;
    while (!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
  
    while (*s != '\0') {

        I2C2TRN = *s;
        while (!IFS3bits.MI2C2IF);
        IFS3bits.MI2C2IF = 0;
       
        s++;
        if (*s == '\0') {
            I2C2TRN = 0b01000000;
            while (!IFS3bits.MI2C2IF);
            IFS3bits.MI2C2IF = 0;
        } else {
            I2C2TRN = 0b11000000;
            while (!IFS3bits.MI2C2IF);
            IFS3bits.MI2C2IF = 0;
        }
 
    }
    
        //stop bit
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
}
