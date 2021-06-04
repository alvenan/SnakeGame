#ifndef __LCD_H__
#define __LCD_H__

#include "defs.h"
#define F_CPU 16000000UL
#include <avr/io.h>

#define LCD_DATA4_TRIS   (ddrd.bit4)
#define LCD_DATA4_IO     (portd.bit4)
#define LCD_DATA5_TRIS   (ddrd.bit5)
#define LCD_DATA5_IO     (portd.bit5)
#define LCD_DATA6_TRIS   (ddrd.bit6)
#define LCD_DATA6_IO     (portd.bit6)
#define LCD_DATA7_TRIS   (ddrd.bit7)
#define LCD_DATA7_IO     (portd.bit7)

#define LCD_RS_TRIS      (ddrb.bit0)
#define LCD_RS_IO        (portb.bit0)
#define LCD_EN_TRIS      (ddrb.bit1)
#define LCD_EN_IO        (portb.bit1)

//Comandos do LCD
#define LCD_Clear             (0x01)
#define LCD_Shift_Left        (0x18)
#define LCD_Shift_Right       (0x1C)
#define LCD_Cursor_Off        (0X0C)
#define LCD_Cursor_Blink      (0X0D)
#define LCD_Cursor_Alt        (0X0F)
#define LCD_Cursor_Home       (0X02)


void DisplayLCD_Out( unsigned char Linha, unsigned char Coluna, char *TextoLCD );
void DisplayLCD_Out_Cp( char *TextoLCD);
void DisplayLCD_Chr( unsigned char Linha, unsigned char Coluna,  char TChar );
void DisplayLCD_Chr_Cp( char TChar );
void DisplayLCD_Cmd( unsigned char Data );
void DisplayLCD_Init( void ); 

//---------------------------------------
void LCD_Enable( void );
void LCD_Write_Data(unsigned char RS, unsigned char Data);




#endif	/* LCD_H */

