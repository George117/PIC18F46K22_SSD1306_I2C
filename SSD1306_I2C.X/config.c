/*
 * File:   config.c
 * Author: georg
 *
 * Created on January 1, 2017, 1:37 PM
 */

#define _XTAL_FREQ 64000000
#include <xc.h>
#include <pic18f46k22.h>
#include "bit_settings.h"
#include "i2c.h"


void config()
{

    OSCCONbits.IRCF0=1;
    OSCCONbits.IRCF1=1;//16Mhz
    OSCCONbits.IRCF2=1;
    OSCTUNEbits.PLLEN = 1; // turn on the PLL 64 MHz
    INTCONbits.GIE=0;

    ANSELA=0X00;
    ANSELB=0X00;
    ANSELC=0X00;
    ANSELD=0X00;
    ANSELE=0X00;
    TRISA=0X00;
    TRISB=0X00;
    TRISC=0X00;
    TRISD=0X00;
    TRISE=0X00;
    PORTA=0X00;
    PORTB=0X00;
    PORTC=0X00;
    PORTD=0X00;
    PORTE=0X00;
    LATA=0X00;
    LATB=0X00;
    LATC=0X00;
    LATD=0X00;
    LATE=0X00;
    
    TRISCbits.TRISC3=1;//i2c
    TRISCbits.TRISC4=1;//i2c
    I2C_Master_Init(100000);
    __delay_ms(100);
    
}



