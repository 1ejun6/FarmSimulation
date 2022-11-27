/*
 * File:   Intiallise.c
 * Author: Jun
 *
 * Created on 10 August, 2022, 1:41 PM
 */

#include <xc.h>
#include "config.h"

// Timer0 for 180s
void initSysDevices0(void) {

    INTCONbits.GIE = 0; // Disable Global Interrupt

    T0CON0 = 0x90;
    T0CON1 = 0x4C;
    TMR0H = 0x54;
    TMR0L = 0x56;

    PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
    PIE0bits.TMR0IE = 1; // Enable Timer0
    PIR0bits.INTF = 0; // Clear external INT flag
    INTPPS = 0x05; // Map external INT to RA5
    INTCONbits.INTEDG = 0; // Configure for rising edge
    PIE0bits.INTE = 1; // Enable external INT interrupt

    INTCONbits.GIE = 1; // Enable Global Interrupt
}

// PWM initialisation 
void initSysDevices1(void) {

    CCPTMRS1 = 0b00000100; // Select Timer2 as base timer for PWM6
    PWM6CON = 0b00000000; // Disable PWM first, set PWM to active high
    T2PR = 124; // Set the period with T2 period register
    PWM6DCH = 0x7D; // Set the duty cycle high byte
    PWM6DCL = 0x00; // Set the duty cycle low byte
    T2CON = 0b11110000; // Enable Timer2, set prescaler, postscal-er
    T2CLKCON = 0b00000001; // Select clock source for Timer2 as Fosc/4
    RD3PPS = 0x0E; // Route PWM6 waveform to RD3

}

// PORT initialisation
void initSysPins(void) {

    ANSELA = 0x00;
    TRISA = 0xFF;

    ANSELB = 0x00;
    TRISB = 0xC1;

    ANSELC = 0x00;
    TRISC = 0x01;

    ANSELD = 0x00;
    TRISD = 0x00;

    ANSELE = 0x0F;
    TRISE = 0xFE;
}

