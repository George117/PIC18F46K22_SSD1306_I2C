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
    unsigned x_axis = 0;
    config();
    OLED_Init(0x3C);
    
    while(1)
    {  
        //LATDbits.LATD0=1;
        
        //OLED_string("HelloWorld", 77, 24);
        for(int i=0;i<128;i++)
        {
            for(int j=0;j<32;j++)
            {
                OLED_pixel(i,j,1);
                
            }
        }    
        
        OLED_write();
        OLED_clear(); 
        
        LATDbits.LATD0=~LATDbits.LATD0;
       
 
    }
}
