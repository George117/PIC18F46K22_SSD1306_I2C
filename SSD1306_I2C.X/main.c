/*
 * File:   main.c
 * Author: georg
 *
 * Created on September 29, 2018, 4:04 PM
 */

#define _XTAL_FREQ 64000000
#include <xc.h>
#include <pic18f46k22.h>
#include "bit_settings.h"
#include "config.h"

void main(void) 
{
    config();
    while(1)
    {
        LATDbits.LATD0 = 1;
        __delay_ms(10);
        LATDbits.LATD0 = 0;
        __delay_ms(10);
    }
}
