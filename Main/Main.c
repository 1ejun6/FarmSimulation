/*
 * File:   main.c
 * Author: Jun
 *
 * Created on 11 August, 2022, 9:58 AM
 */

#include <xc.h>
#include"config.h"
unsigned char dig3, dig2, dig1, dig0;
int onoff = 1;

void main(void) {

    initSysPins();
    initSysDevices0();
    initLCD();
    CLEAR;
    CPUDOZE = 0;
    MOTOR = 0;
    SPEAKER = 0;
    clearPORT();

    while (1) {

        unsigned char key;
        while (1) {
            startUp();
            lcdWriteMessage("1 R1 2 R2 3 R3", 1, 1);
            lcdWriteMessage("FOR SIMULATION", 2, 1);
            key = getKey();
            while ((key = getKey()) == 0);
            getKeyPad(key);
            while ((key = getKey()) == 0);
        }
    }
}

// KeyPad Switch Case
void getKeyPad(unsigned char key) {
    initSysDevices1();
    unsigned int pv;
    SPEAKER = 0;

    // Condition while loop (onoff)
    
    switch (key) {

        case 'B':
            CLEAR;
            lcdWriteMessage("ENTER VERIFY", 1, 1);
            lcdWriteMessage("KEY 2 STOP", 2, 1);
            
            while (onoff) {
                breakIn();
                key = getKey();
                if (key == 'A') { // Cancel the Alarm
                    CLEAR;
                    lcdWriteMessage("CORRECT KEY", 1, 1);
                    onoff = 0;
                    SPEAKER = 0;
                } else {
                    CLEAR;
                    lcdWriteMessage("WRONG KEY", 1, 1);
                    lcdWriteMessage("TRY AGAIN", 2, 1);
                    breakIn();
                }
            }
            onoff= 1; // On the condition back
            break;

        case '1':
            CLEAR;
            lcdWriteMessage("THE LM35 IS", 1, 1);
            lcdWriteMessage("SELECTED", 2, 1);
            __delay_ms(1000);
            CLEAR;
            
            while (onoff) {
                key = getKey();
                if (key == 'C') { // Cancel the LM35 function
                    CLEAR;
                    MOTOR = 0;
                    lcdWriteMessage("CANCEL", 1, 1);
                    onoff = 0;
                }
                LM35();
            }
            onoff = 1; // On the condition back
            break;

        case '2':
            CLEAR;
            SPEAKER = 0;
            lcdWriteMessage("THE PHLEVEL IS", 1, 1);
            lcdWriteMessage("SELECTED", 2, 1);
            __delay_ms(1000);
            CLEAR;
            
            while (onoff) {
                key = getKey();
                if (key == 'C') { // Cancel the PHLevel function
                    CLEAR;
                    lcdWriteMessage("CANCEL", 1, 1);
                    onoff = 0;
                }
                PHLevel();
            }
            onoff = 1; // On the condition back
            break;

        case '3':
            CLEAR;
            SPEAKER = 0;
            int pwm = 1;
            pwmDefault();
            
            while (onoff) {
                key = getKey();
                if (key == 'C') { // Cancel the Irrigation function
                    CLEAR;
                    lcdWriteMessage("CANCEL", 1, 1);
                    onoff = 0;
                    MOTOR = 0;
                    PWM6CONbits.EN = 0;
                } else if (key == '4') {
                    CLEAR;
                    while (pwm) { // (PWM) is the level while loop condition 
                        lcdWriteMessage("LEVEL 2", 1, 1);
                        pv = 150; 
                        PWM6DCH = pv >> 2;
                        PWM6DCL = (pv % 4) << 6;
                        key = getKey();
                        if (key == 'F') { // Cancel the Irrigation Level
                            CLEAR;
                            pwm = 0;
                            pwmDefault(); // Call the Irrigation function original levels of 50
                        }
                    }
                    pwm = 1;
                } else if (key == '5') {
                    CLEAR;
                    while (pwm) { // (PWM) is the level while loop condition 
                        lcdWriteMessage("LEVEL 3", 1, 1);
                        pv = 300; 
                        PWM6DCH = pv >> 2;
                        PWM6DCL = (pv % 4) << 6;
                        key = getKey();
                        if (key == 'F') { // Cancel the Irrigation Level
                            CLEAR;
                            pwm = 0;
                            pwmDefault(); // Call the Irrigation function original levels of 50
                        }
                    }
                    pwm = 1;
                } else if (key == '6') {
                    CLEAR;
                    while (pwm) { // (PWM) is the level while loop condition 
                        lcdWriteMessage("LEVEL 4", 1, 1);
                        pv = 500; 
                        PWM6DCH = pv >> 2;
                        PWM6DCL = (pv % 4) << 6;
                        key = getKey();
                        if (key == 'F') { // Cancel the Irrigation Level
                            CLEAR;
                            pwm = 0;
                            pwmDefault(); // Call the Irrigation function original levels of 50
                        }
                    }
                    pwm = 1;
                }
            }
            onoff = 1;
            break;
    }
}

// PWM main function
void pwmDefault(void) {

    lcdWriteMessage("IRRIGATION", 1, 1);
    lcdWriteMessage("PRESS 4, 5, 6", 2, 1);
    PWM6CONbits.EN = 1;
    unsigned int pv = 50; // 25% of 500 (max)
    PWM6DCH = pv >> 2;
    PWM6DCL = (pv % 4) << 6;

}

// PHLevel main function
void PHLevel(void) {

    initADCPH();
    PORTB = 0x00; // Off LED
    unsigned int result;

    result = readPHLevel();
    dig1 = (unsigned char) (result / 10);
    dig0 = (unsigned char) (result % 10);
    disp7seg();

    lcdWriteMessage("PH LEVEL:  ", 1, 1);
    lcdWriteData(dig1 + 0x30);
    lcdWriteData(dig0 + 0x30);

    if (result < 7) {
        PORTB = PORTB^0x04;
        __delay_ms(100);
        lcdWriteMessage("TOO BASE  ", 2, 1);
    } else if (result == 7) {
        PORTB = PORTB^0x08;
        lcdWriteMessage("JUST RIGHT", 2, 1);
    } else if (result > 7 && result <= 14) {
        PORTB = PORTB^0x02;
        __delay_ms(100);
        lcdWriteMessage("TOO ACIDIC", 2, 1);
    } else {
        PORTB = 0x00;
        __delay_ms(100);
        lcdWriteMessage("ERROR     ", 1, 1);
    }
}

// LM35 main function
void LM35(void) {

    initADCLM35();
    initSysDevices1(); // PWM intialisation
    PORTB = 0x00;
    unsigned int result;
    unsigned int pv;
    result = readLM35();
    //range 0-99
    dig1 = (unsigned char) ((result % 100) / 10);
    dig0 = (unsigned char) (result % 10);

    lcdWriteMessage("LM35 TEMP: ", 1, 1);
    lcdWriteData(dig1 + 0x30);
    lcdWriteData(dig0 + 0x30);

    if (result < 24) {
        lcdWriteMessage("TOO COLD", 2, 1);
    } else if (result == 24) {
        lcdWriteMessage("NORMAL  ", 2, 1);
    } else if (result > 27) {
        lcdWriteMessage("TOO HOT ", 2, 1);

        // Sprinker On
        for (int i = 0; i < 2; i++) {
            PWM6CONbits.EN = 1;
            pv += 250;
            __delay_ms(50);

            if (pv > 500) {
                pv = 0;
            }
            PWM6DCH = pv >> 2;
            PWM6DCL = (pv % 4) << 6;
        }
        PWM6CONbits.EN = 0;
    }
}