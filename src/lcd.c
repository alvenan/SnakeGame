#include "lcd.h"

#include <util/delay.h>

//****************************Fun��es
void LCD_Write_Data(unsigned char RS, unsigned char Data) {
    //*****************************************************************************
    // exemplo: Data   10110010
    //              & 00010000 (ou 0x10;  observa��o: lembre-se que & � bit a
    //              bit)
    //                --------
    //              = 00010000
    // agora
    //                00010000
    //             == 00010000 (ou 0x10)
    //                --------
    //              = 1        (retorna 1)
    //*****************************************************************************

    LCD_RS_IO = RS;  // 0

    _delay_ms(2);
    LCD_DATA4_IO = ((Data & 0x10) == 0x10);
    LCD_DATA5_IO = ((Data & 0x20) == 0x20);
    LCD_DATA6_IO = ((Data & 0x40) == 0x40);
    LCD_DATA7_IO = ((Data & 0x80) == 0x80);

    LCD_Enable();

    Data = Data << 4;  // Rotaciona o nibble o LSB para a posi��o MSB
    LCD_DATA4_IO = ((Data & 0x10) == 0x10);
    LCD_DATA5_IO = ((Data & 0x20) == 0x20);
    LCD_DATA6_IO = ((Data & 0x40) == 0x40);
    LCD_DATA7_IO = ((Data & 0x80) == 0x80);

    LCD_Enable();
}

void LCD_Enable(void)  // INSTRU��O DE CLOCK PARA O LCD
{
    _delay_us(40);
    LCD_EN_IO = 1;
    _delay_us(40);
    LCD_EN_IO = 0;
    _delay_us(40);
}

void DisplayLCD_Cmd(unsigned char CmdLCD) {
    LCD_Write_Data(0, CmdLCD);  // RS = 0, -> COMANDO A SER PROCESSADO
}

void DisplayLCD_Chr_Cp(char Tchar) {
    LCD_Write_Data(1, Tchar);  // RS = 1 -> DADO A SER ESCRITO
}

// fun��es
void DisplayLCD_Init(void) {
    LCD_DATA4_TRIS = 1;
    LCD_DATA4_IO = 0;
    LCD_DATA5_TRIS = 1;
    LCD_DATA5_IO = 0;
    LCD_DATA6_TRIS = 1;
    LCD_DATA6_IO = 0;
    LCD_DATA7_TRIS = 1;
    LCD_DATA7_IO = 0;
    LCD_EN_TRIS = 1;
    LCD_RS_IO = 0;
    LCD_RS_TRIS = 1;
    LCD_RS_IO = 0;

    _delay_ms(100);  // Tempo necess�rio para inicializa��o do LCD ap�s power-on

    LCD_DATA4_IO = 1;
    LCD_DATA5_IO = 1;
    LCD_Enable();
    LCD_Enable();
    LCD_Enable();

    _delay_ms(1);

    LCD_DATA4_IO = 0;
    LCD_DATA5_IO = 1;
    LCD_Enable();
    LCD_Enable();
    LCD_Enable();

    _delay_ms(1);

    DisplayLCD_Cmd(0X28);  // 2X linhas 7x5 em modo 4bits
    DisplayLCD_Cmd(0X0C);
    DisplayLCD_Cmd(0X06);
    DisplayLCD_Cmd(0X01);

    _delay_ms(100);
}

// DisplayLCD_Out(1,2, "BOM DIA");
void DisplayLCD_Out(unsigned char Linha, unsigned char Coluna, char *TextoLCD) {
    LCD_RS_IO = 0;  // TRATAR PRIMEIRO AS COORDENADAS X E Y
    switch (Linha) {
        case 1: {
            Coluna = Coluna + 0X7F;  // 2 + 0X7F = 0X81
            LCD_Write_Data(
                0, Coluna);  // Comando, visto que estamos posicionando o cursor
            // LCD_Enable();
            break;
        }
        case 2: {
            Coluna = Coluna + 0xBF;  // 2 + 0xBF = 0XC1
            LCD_Write_Data(0, Coluna);
            // LCD_Enable();
            break;
        }
    }
    DisplayLCD_Out_Cp(TextoLCD);  // Escreve no LCD "BOM DIA"
}

// DisplayLCD_Out_Cp("BOM DIA");
void DisplayLCD_Out_Cp(char *Ponteiro) {
    // LCD_RS_IO = 1;  //ESCREVER UM DADO
    while (*Ponteiro)  // loop at� encontrar o caractere NULL (ZERO)
    {
        LCD_Write_Data(1, *Ponteiro);  // RS =1, ESCREVENDO NO LCD
        // LCD_Enable();
        ++Ponteiro;
    }
}

// DisplayLCD_Chr_Cp(1,6,'A');
void DisplayLCD_Chr(unsigned char Linha, unsigned char Coluna, char Tchar) {
    LCD_RS_IO = 0;  // TRATAR PRIMEIRO AS COORDENADAS X E Y
    switch (Linha) {
        case 1: {
            Coluna = Coluna + 0x7F;
            LCD_Write_Data(0, Coluna);
            // LCD_Enable();
            break;
        }
        case 2: {
            Coluna += 0xBF;
            LCD_Write_Data(0, Coluna);
            // LCD_Enable();
            break;
        }
    }
    DisplayLCD_Chr_Cp(Tchar);  // ESCREVE NO LCD
}
