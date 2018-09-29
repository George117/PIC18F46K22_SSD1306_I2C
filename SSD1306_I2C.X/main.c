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
#include "i2c.h"


void main(void) 
{
    config();
    
    I2C_Master_Start();
    I2C_Write_Display(adress);
	I2C_Write_Display(0x69);
    I2C_Master_Stop();
    
    while(1)
    {
        __delay_ms(100);
        I2C_Master_Start();
        I2C_Write_Display(adress);
        I2C_Write_Display(0x69);
        I2C_Master_Stop();
        __delay_ms(100);
    }
}
