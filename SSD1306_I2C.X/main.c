/*
 * File:   main.c
 * Author: georg
 *
 * Created on September 29, 2018, 4:04 PM
 */

#define _XTAL_FREQ 64000000
#define adress 0x3C //70

#include <xc.h>
#include <pic18f46k22.h>
#include "bit_settings.h"
#include "config.h"
#include "oled.h"

void main(void) 
{
    config();
    OLED_Init(0x3C);
    
    while(1)
    {   
        OLED_clear();
        OLED_string("Hello World!\0", 0, 0);
        OLED_write();
        __delay_ms(100);
        OLED_clear();
        OLED_string("Hello World!\0", 0, 0);
        OLED_write();
        __delay_ms(100);
    }
}
