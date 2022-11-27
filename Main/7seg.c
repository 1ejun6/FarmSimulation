/*
 * File:   7Seg.c
 * Author: Jun
 *
 * Created on 10 August, 2022, 1:35 PM
 */


#include <xc.h>
#include "config.h"
unsigned char dig1, dig0;

// Our own segTable
const unsigned char segTable[] = {

    0x81, //0 0b1010 0000
    0xF9, //1
    0x43, //2
    0x61, //3
    0x39, //4
    0x25, //5
    0x05, //6
    0xF1, //7
    0x01, //8
    0x21, //9
    0xFF // Blank

};

// Display the 7seg
void disp7seg(void) {
    
    //D2
    PORTDbits.RD1 = 1; //SL1
    PORTDbits.RD0 = 0; //SL2
    PORTC = segTable[dig0];
    __delay_ms(300);
    PORTC = segTable[10];

    //D1
    PORTDbits.RD1 = 0; //SL1
    PORTDbits.RD0 = 1; //SL2
    PORTC = segTable[dig1];
    __delay_ms(300);
    PORTC = segTable[10];

}