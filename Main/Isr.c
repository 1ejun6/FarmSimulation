/*
 * File:   isr.c
 * Author: Jun
 *
 * Created on 4 August, 2022, 1:28 AM
 */


#include <xc.h>
#include "config.h"

void __interrupt() isr(void) {

    // Timer0 to go sleep mode
    if (PIR0bits.TMR0IF == 1) // Check Timer0 interrupt flag
    {
        PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
        clearPORT();
        CLEAR;
        lcdWriteMessage("SLEEP MODE IS ON", 1, 1);
        CPUDOZE = 0;
        SLEEP();
        TMR0H = 0x54;
        TMR0L = 0x56;
      
    }

    // Isr to wake up
    if (PIR0bits.INTF == 1) {
        PIR0bits.INTF = 0; //clear int flag}
    }

}

// Off the 7Seg & LED
void clearPORT(void) {
    PORTB = 0x00;
    PORTC = 0xFF;
}