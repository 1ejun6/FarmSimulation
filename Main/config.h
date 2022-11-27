#pragma config FEXTOSC = XT
#pragma config WDTE = OFF
#pragma config LVP = OFF
#define _XTAL_FREQ 4000000


// Function declaration & Define certain ports 
#define CLEAR lcdWriteCtrl(0x01); // Clear LCD

void initSysPins(void);
void initSysDevices0(void);
void clearPORT(void);

void initADCPH(void);
void PHLevel(void);
unsigned int readPHLevel(void);

#define convertRawToCelsius 500/1024
void initADCLM35(void);
unsigned int readLM35(void);
void LM35(void);

#define LCD_DATA PORTD // Port used by LCD
#define LCD_RS PORTBbits.RB4 // RS signal for LCD
#define LCD_E PORTBbits.RB5 // E signal for LCD
void initLCD(void);
void lcdWriteCtrl(char);
void lcdWriteData(char);
void lcdWriteMessage(unsigned char message[], unsigned char row, unsigned char startPos);
void lcdSetPosition(unsigned char row, unsigned char col);

#define KEY_DA PORTAbits.RA4
unsigned char getKey(void);
void getKeyPad(unsigned char key);

#define MOTOR PORTDbits.RD3
void initPWMLM35(void);

void disp7seg(void);

void __interrupt() isr(void);

#define SPEAKER PORTDbits.RD2
void startUp(void);
void breakIn(void);
void s1100(void);
void s700(void);

void initSysDevices1(void);

void pwmDefault(void);