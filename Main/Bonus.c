/*
 * File:   Bonus.c
 * Author: Jun
 *
 * Created on 10 August, 2022, 2:45 PM
 */

#include <xc.h>
#include "config.h"

// Start up of the board speaker sound
void startUp(void) {

    for (unsigned int cnt = 0; cnt < 500; cnt++) // Produce 1 kHz tone for 1sec
    {
        SPEAKER = 1;
        __delay_us(200);

        SPEAKER = 0;
        __delay_us(200);
    }
    for (unsigned int cnt = 0; cnt < 400; cnt++) // Produce 1 kHz tone for 1sec
    {
        SPEAKER = 1;
        __delay_us(500);

        SPEAKER = 0;
        __delay_us(500);
    }
    for (unsigned int cnt = 0; cnt < 400; cnt++) // Produce 1 kHz tone for 1sec
    {

        SPEAKER = 1;
        __delay_us(150);

        SPEAKER = 0;
        __delay_us(150);
    }
    for (unsigned int cnt = 0; cnt < 400; cnt++) // Produce 1 kHz tone for 1sec
    {
        SPEAKER = 1;
        __delay_us(200);

        SPEAKER = 0;
        __delay_us(200);
    }
    for (unsigned int cnt = 0; cnt < 500; cnt++) // Produce 1 kHz tone for 1sec
    {
        SPEAKER = 1;
        __delay_us(500);

        SPEAKER = 0;
        __delay_us(500);
    }
}

// Alarm system sound 
void breakIn(void) {
    s1100();
    s700();
    s1100();
    s700();
    s1100();
    s700();
    s1100();
    s700();
}

void s1100(void) {

    for (unsigned int cnt = 0; cnt < 300; cnt++) // Produce 1 kHz tone for 1sec
    {
        SPEAKER = 1;
        __delay_us(1100);

        SPEAKER = 0;
        __delay_us(1100);
    }

}

void s700(void) {

    for (unsigned int cnt = 0; cnt < 150; cnt++) // Produce 1 kHz tone for 1sec
    {
        SPEAKER = 1;
        __delay_us(700);

        SPEAKER = 0;
        __delay_us(700);
    }

}