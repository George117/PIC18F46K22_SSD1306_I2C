#define _XTAL_FREQ 64000000
#include <pic18f46k22.h>
#include <htc.h>
#include "oled.h"
#include <string.h>

void I2CInit(void){
    unsigned c = 100000; 
	SSPCON1 = 0b00101000;
    SSPCON2 = 0x00;
    SSPADD = (_XTAL_FREQ/(4*c))-1;
    SSPSTAT = 0x00;
    TRISCbits.TRISC3=1;
    TRISCbits.TRISC4=1;
}
void I2CStart(){
	SSPCON2bits.SEN = 1;while(SSPCON2bits.SEN);
}
void I2CStop(){
	SSPCON2bits.PEN = 1;while(SSPCON2bits.PEN);
}
void I2CSend(char dat) {
	SSPBUF = dat; while(SSP1STATbits.BF);
	while ((SSPCON2 & 0b00011111 ) || ( SSPSTAT & 0b00000100 ) );
}

void OLED_Init(char address) {
    _address = address << 1;
    I2CInit();
    __delay_ms(4);
    OLED_command(OLED_DISPLAYOFF);         // 0xAE
    OLED_command(OLED_SETDISPLAYCLOCKDIV); // 0xD5
    OLED_command(0x80);                    // the suggested ratio 0x80
    OLED_command(OLED_SETMULTIPLEX);       // 0xA8
    OLED_command(0x1F);
    OLED_command(OLED_SETDISPLAYOFFSET);   // 0xD3
    OLED_command(0x0);                        // no offset
    OLED_command(OLED_SETSTARTLINE | 0x0); // line #0
    OLED_command(OLED_CHARGEPUMP);         // 0x8D
    OLED_command(0xAF);
    OLED_command(OLED_MEMORYMODE);         // 0x20
    OLED_command(0x00);                    // 0x0 act like ks0108
    OLED_command(OLED_SEGREMAP | 0x1);
    OLED_command(OLED_COMSCANDEC);
    OLED_command(OLED_SETCOMPINS);         // 0xDA
    OLED_command(0x02);
    OLED_command(OLED_SETCONTRAST);        // 0x81
    OLED_command(0x8F);
    OLED_command(OLED_SETPRECHARGE);       // 0xd9
    OLED_command(0xF1);
    OLED_command(OLED_SETVCOMDETECT);      // 0xDB
    OLED_command(0x40);
    OLED_command(OLED_DISPLAYALLON_RESUME);// 0xA4
    OLED_command(OLED_NORMALDISPLAY);      // 0xA6
    OLED_command(OLED_DISPLAYON);          //--turn on oled panel

}
void OLED_command(char command) {

    I2CStart();             //StartI2C();
    I2CSend(_address);  //send address
    I2CSend(0x00);          //send data incomming
    I2CSend(command);       //send command
    I2CStop();              //StopI2C();
}
void OLED_data( char data) {

    I2CStart();             //StartI2C();
    I2CSend(_address);      //send address
    I2CSend(0x40);          //send data incomming
    I2CSend(data);          //send data
    I2CStop();              //StopI2C();
}
void OLED_write(){
   unsigned x;
   OLED_command(OLED_COLUMNADDR) ;
   OLED_command(0x00);
   OLED_command(127);
   OLED_command(OLED_PAGEADDR);
   OLED_command(0x00);
   OLED_command(3);

   I2CStart();
   I2CSend(_address) ;
   I2CSend(0x40) ;
   for(x = 0; x < (128 * 32 / 8); x++)
   {
      I2CSend(OLED_buffer[x]);
   }
   I2CStop();
}
void OLED_clear(){
    memset(OLED_buffer, 0, 128 * 32 / 8);
}
void OLED_invert(){
    OLED_command(OLED_INVERTDISPLAY);
}
void OLED_rscroll(char start, char stop) {
    OLED_command(0x26);
    OLED_command(0X00);
    OLED_command(start);
    OLED_command(0X00);
    OLED_command(stop);
    OLED_command(0X00);
    OLED_command(0XFF);
    OLED_command(0x2F); //Activate scroll
}
void OLED_lscroll(char start, char stop) {
    OLED_command(0x27);
    OLED_command(0X00);
    OLED_command(start);
    OLED_command(0X00);
    OLED_command(stop);
    OLED_command(0X00);
    OLED_command(0XFF);
    OLED_command(0x2F); //Activate scroll
}
void OLED_stopscroll() {
    OLED_command(0x2E);
}
void OLED_pixel(short x, short y, char color){ //hmm, dosent include error checking..
    char y_bit = y%8;
    short y_row = (y - y_bit)*16 + x;
    OLED_buffer[y_row] |= (color?1:0) << y_bit;
}
void OLED_char(char character, short x, short y) {
    short table_offset = (character-0x20)*5;
    short offset = y*16 + x;
    char i = 0;
    for(; i < 5; i++) OLED_buffer[i+offset] = OLED_characters[i+table_offset];
}
void OLED_string(char* str, short x, short y) {

    short pos = 0;
    char character = str[pos++];
    short startx = x;
    short starty = y;
    while(character != '\0') {
        OLED_char(character, startx, starty);
        if(startx >= 123) starty++; //wrap around
        startx += 5;
        character = str[pos++];
    }
}