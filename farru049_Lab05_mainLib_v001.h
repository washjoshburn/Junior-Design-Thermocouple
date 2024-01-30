/* 
 * File:   farru049_Lab05_mainLib_v001.h
 * Author: stone
 *
 * Created on July 19, 2023, 12:29 PM
 */

#ifndef FARRU049_LAB05_MAINLIB_V001_H
#define	FARRU049_LAB05_MAINLIB_V001_H

#ifdef	__cplusplus
extern "C" {
#endif

void lcd_shift(int dir);
void delay (unsigned int ms);
void lcd_cmd(char Package);
void lcd_init(void);
void lcd_setCursor(char x, char y);
void lcd_printChar(char myChar);
void lcd_printStr(const char *s);



#ifdef	__cplusplus
}
#endif

#endif	/* FARRU049_LAB05_MAINLIB_V001_H */

