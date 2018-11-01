/*
 * File:   newmain.c
 * Author: jmpasquali
 *
 * Created on 28 de Setembro de 2018, 21:28
 */


// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = EC_EC     // Oscillator Selection bits (EC oscillator, CLKO function on RA6 (EC))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include "My_adc.h"

#define _XTAL_FREQ 20000000     // Usar cristal de 20MHz  	

#define NUM_0 0b00111111 //0x3F 
#define NUM_1 0b00000110 //0x3F 
#define NUM_2 0b01011011 //0x3F 
#define NUM_3 0b01001111 //0x3F 
#define NUM_4 0b01100110 //0x3F 
#define NUM_5 0b01101101 //0x3F 
#define NUM_6 0b01111101 //0x3F 
#define NUM_7 0b00000111 //0x3F 
#define NUM_8 0b01111111 //0x3F 
#define NUM_9 0b01101111 //0x3F 

#define DISPD PORTCbits.RC0
#define DISPU PORTCbits.RC1
#define ALERTA_1  PORTAbits.RA4
#define ALERTA_2  PORTAbits.RA5 
#define ALERTA_3  PORTCbits.RC5 

void ADC_Init() {
    //    TRISA = 0xff; /*set as input port*/
    TRISA = 0b00001011;
    ADCON1 = 0b00001011;
    //  ADCON1 = 0x00; /*ref vtg is VDD and Configure pin as analog pin*/
    ADCON2 = 0x92; /*Right Justified, 4Tad and Fosc/32. */
    ADRESH = 0; /*Flush ADC output Register*/
    ADRESL = 0;
}

int ADC_Read(int channel) {
    int digital;
    ADCON0 = (ADCON0 & 0b11000011) | ((channel << 2) & 0b00111100); /*channel is selected i.e (CHS3:CHS0) 
                                                                      and ADC is disabled i.e ADON=0*/
    ADCON0 |= ((1 << ADON) | (1 << GO)); /*Enable ADC and start conversion*/
    while (ADCON0bits.GO_nDONE == 1); /*wait for End of conversion i.e. Go/done'=0 conversion completed*/
    digital = (ADRESH * 256) | (ADRESL); /*Combine 8-bit LSB and 2-bit MSB*/
    return (digital);
}

int sensorTemperatura() {

    float var = 0;

    var = (ADC_Read(3)*4.88);
    var = (var / 10.00);

    return (int) var;
}

void myDelay(int tempo) {
    int i;
    for (i = 0; i < tempo; i++) {
        __delay_ms(1);
    }
}

void enviaDigito(int valor) {

    if (valor == 0)
        PORTB = NUM_0;
    else if (valor == 1)
        PORTB = NUM_1;
    else if (valor == 2)
        PORTB = NUM_2;
    else if (valor == 3)
        PORTB = NUM_3;
    else if (valor == 4)
        PORTB = NUM_4;
    else if (valor == 5)
        PORTB = NUM_5;
    else if (valor == 6)
        PORTB = NUM_6;
    else if (valor == 7)
        PORTB = NUM_7;
    else if (valor == 8)
        PORTB = NUM_8;
    else if (valor == 9)
        PORTB = NUM_9;
    else
        PORTB = 0x00;
}

void mostraTemp() { // Shows temperature from LM35 to 7seg displays

    int temperatura;

    if ((temperatura = sensorTemperatura()) > 99)
        temperatura = 99;

    PORTD = 0x00;

    DISPD = 1;
    DISPU = 0;
    enviaDigito(temperatura / 10);
    myDelay(60);
    DISPD = 0;
    DISPU = 1;
    enviaDigito(temperatura % 10);
    myDelay(60);

}

void main(void) {

    // Set ports     
    TRISB = 0b00000000;  
    TRISC = 0b00000000;
    
    ADC_Init();
    
    //  PIC's analog comparator configuration
    CMCON = 0b00110101;

    PORTB = 0x00;
    PORTD = 0b00011100;
    
    //Blinks LED if temperature read by LM35 is higher than 100 C
    while (1) {

        ALERTA_3 = 1;
        mostraTemp();

        if (sensorTemperatura() > 100) {
            ALERTA_3 = 0;
            myDelay(10);
        }

        mostraTemp();
    }
}
