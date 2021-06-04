/**
 * Necessário para usar as macros (ex: _delay_ms);
 */
#define F_CPU 16000000UL

/**
 * Inclui as definições dos registrados do ATMEGA328p ou ATMEGA2560;
 */
#include <avr/io.h>

/**
 * Necessário para usar as interrupções do AVR;
 */
#include <avr/interrupt.h>

/**
 * Biblioteca que inclui a macro _delay_ms;
 */
#include <util/delay.h>

/**
 * Lib C
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Lib lcd
 */
#include "lcd.h"

/**
 * Diretivas
 */
#define TRUE 1

/**
 * Função principal e de entrada do programa;
 */
int main(void) {
    unsigned int count = 0;
    char string[10];
    /**
     * Inicializa o Display LCD;
     */
    DisplayLCD_Init();
    DisplayLCD_Cmd(LCD_Clear);
    DisplayLCD_Cmd(LCD_Cursor_Off);
    DisplayLCD_Out(1, 1, (char*)"Display 16x2");
    DisplayLCD_Out(2, 1, "Count:");

    for (;;) {
        count++;
        sprintf((char*)string, "%d ", count);
        DisplayLCD_Out(2, 7, (char*)string);
        _delay_ms(200);
    }

    return 0;
}
