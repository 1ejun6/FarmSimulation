/*
 * File:   lcd.c
 * Author: Jun
 *
 * Created on 7 July, 2022, 1:48 PM
 *
 */

#include <xc.h>
#include "config.h"

void initLCD() {

    __delay_ms(15); // a) 15ms LCD power-up delay
    lcdWriteCtrl(0b00000011); // b) Function Set (DB4-DB7:8-bit interface)
    __delay_ms(5); // c) 5ms delay
    lcdWriteCtrl(0b00000010); // d) Function Set (DB4-DB7:4-bit interface)
    lcdWriteCtrl(0b00101000); // Function Set - 4-bit, 2 lines, 5x7
    lcdWriteCtrl(0b00001100); // Display on, cursor off
    lcdWriteCtrl(0b00000110); // Entry mode - inc addr, no shift
    lcdWriteCtrl(0b00000001); // Clear display & home position

}

void lcdWriteCtrl(char x) {

    LCD_RS = 0;
    LCD_DATA = x;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
    LCD_DATA = x << 4;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);

}

void lcdWriteData(char x) {

    LCD_RS = 1;
    LCD_DATA = x;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
    LCD_DATA = x << 4;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);

}

void lcdSetPosition(unsigned char row, unsigned char col) {

    unsigned char ramAddr; // Ctrl instruction to be sent
    if (row == 1) // If row is 1:
        ramAddr = 0x00 + col - 1; // Subtract 1 from the col
    else // If row is 2:
        ramAddr = 0x40 + col - 1; // Add 0x40 to ramAddr, and
    // subtract 1 from the col
    lcdWriteCtrl(ramAddr + 0x80); // Add 0x80 to ramAddr and write
    // ctrl instruction

}

// Own function to display message on LCD with row & setpos
void lcdWriteMessage(unsigned char message[], unsigned char row, unsigned char startPos) {

    lcdSetPosition(row, startPos);
    for (unsigned char i = 0; message[i] != 0; i++) {
        lcdWriteData(message[i]); // Display one character
    }

}

// KeyPad
const unsigned char keycode[ ] = "123F456E789DA0BC";

unsigned char getKey(void) {

    unsigned char keybits;
    unsigned char key = 0; // initial key pressed state : 0 means no keys pressed
    if (KEY_DA == 1) { // wait DAV to go HI before reading ABCD
        keybits = (PORTA & 0x0F); //0b0000 1111
        key = keycode[keybits];
    }
    return key;

}

