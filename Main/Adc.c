/*
 * File:   ADC.c
 * Author: Jun
 *
 * Created on 10 August, 2022, 1:31 PM
 */

#include <xc.h>
#include"config.h"

// Initialise the ADC for LM35 
void initADCLM35(void) {
    
    ADREF = 0x00;
    ADCLK = 0x03;
    ADACQ = 0x00;
    ADCON0 = 0b10000100; //Right
    
}

// Initialise the ADC for PHLevel 
void initADCPH(void) {
    
    ADREF = 0x00;
    ADCLK = 0x03;
    ADACQ = 0x00;
    ADCON0 = 0b10000000; //Left
    
}

// The conversion for LM35
unsigned int readLM35(void) {
    
    unsigned int result;
    ADPCH = 0x21; //0b00100001
    __delay_us(5); // add 5 us TACQ manually
    ADCON0bits.ADGO = 1; // start conversion
    while (ADCON0bits.ADGO == 1); // wait for conversion to complete
    result = ADRESH * 256 + ADRESL;
    return (result = result * convertRawToCelsius);
    
}

// The conversion for PHLevel
unsigned int readPHLevel(void) {
    
    unsigned int result;
    ADPCH = 0x22; //ANE2 PORTRE2
    __delay_us(5);
    ADCON0bits.ADGO = 1; //Start conversion
    while (ADCON0bits.ADGO == 1); // Wait until ADGO == 0
    result = ADRESH & 0xF0; //0b11110000;
    return (result = result >> 4); //0-15;
    
}