#include "snake.h"
uint8_t pixel_matrix[8][128]; // Matrix
uint8_t page_line[2];         // [0] -> page; [1] -> line

bool checkPixel(uint8_t line, uint8_t column)
{
        uint8_t mask = 0x00;
        updatePageLine(line);
        mask = 1 << page_line[1];
        return ((pixel_matrix[page_line[0]][column] & mask) !=
                0); // -> return 0 if the pixel is OFF, return 1 if ti is ON
}

void togglePixel(uint8_t line, uint8_t column)
{
        uint8_t page, page_line;
        page_line = line % 8;
        page = (line - page_line) / 8;
        OLED_SetCursor(page, column);

        pixel_matrix[page][column] ^= (1 << page_line);
        oledSendByte(pixel_matrix[page][column]);
}

void updatePageLine(uint8_t line)
{
        page_line[0] = 0x00;
        page_line[1] = 0x00;

        page_line[1] = line % 8;                  // pixel line in the page
        page_line[0] = (line - page_line[1]) / 8; // page
}

static uint8_t inline convertLineToPage(uint8_t line)
{
        return (line/8);
}

static uint8_t inline convertLineToBitPosition(uint8_t line)
{
        return (line % 8);
}

void initPixelMatrix()
{
        for (uint8_t page = 0; page < 8; page++)
        {
                for (uint8_t column = 0; column < 128; column++)
                {
                        pixel_matrix[page][column] = 0x00;
                }
        }
}

blockStatus isEmptyBlock(int blockXPosition, int blockYPosition)
{
        int line;
        int column;

        uint8_t block[BLOCK_SIDE_TOTAL_PIXELS];
        uint8_t blockMask;

        line    = (blockXPosition * BLOCK_SIDE_TOTAL_PIXELS) + 9;
        column  = (blockYPosition * BLOCK_SIDE_TOTAL_PIXELS) + 1;

        OLED_SetCursor(convertLineToPage(line), column);

        oledReceiveStart();

        blockMask = SET_BLOCK_MASK(blockXPosition);

        for (int i = 0; i < BLOCK_SIDE_TOTAL_PIXELS; i++)
        {
                if (i == (BLOCK_SIDE_TOTAL_PIXELS - 1))
                {
                        block[i] = (blockMask & oledReceiveByte(NACK));

                        if (block[i] == blockMask)
                        {
                                return FULL_BLOCK;
                        }
                        else if (block[i] == 0x00)
                        {
                                continue;
                        }
                        else
                        {
                                return UNKOWN_BLOCK;
                        }
                }
                else
                {
                        block[i] = (blockMask & oledReceiveByte(ACK));

                        if (block[i] == blockMask)
                        {
                                return FULL_BLOCK;
                        }
                        else if (block[i] == 0x00)
                        {
                                continue;
                        }
                        else
                        {
                                return UNKOWN_BLOCK;
                        }
                }
        }
        
        return EMPTY_BLOCK;
}

void drawBlock(int blockXPosition, int blockYPosition)
{
        //@TODO: function to draw a block at screen
        //first check if block position is valid

        return 0;
}

void drawFood(snakeDirection dir)
{
        //@TODO: function to randomize which position food will appear
        return 0;
}

int drawSnake(snakeDirection dir)
{
        //@TODO: function to update snake draw at display
        return 0;
}

void drawWall()
{
        for (uint8_t page = 1; page < 8; page++)
        {
                OLED_SetCursor(page, 0);
                for (uint8_t column = 0; column < 128; column++)
                {
                        if ((column == 0) || (column == 127))
                        {
                                pixel_matrix[page][column] = 0xFF;
                                oledSendByte(0xFF);
                        }
                        else if (page == 1)
                        {
                                pixel_matrix[page][column] = 0x01;
                                oledSendByte(0x01);
                        }
                        else if (page == 7)
                        {
                                pixel_matrix[page][column] = 0x80;
                                oledSendByte(0x80);
                        }
                        else
                        {
                                pixel_matrix[page][column] = 0x00;
                                oledSendByte(0x00);
                        }
                }
        }
}



void drawScore(uint8_t score)
{
        OLED_SetCursor(0, 0);
        OLED_Printf("%u", score);
        _delay_ms(100);
}

uint8_t topToBottom(uint8_t data, uint8_t toggle)
{
        uint8_t aux_data = data;
        for (uint8_t page = 0; page < 8; page++)
        {
                OLED_SetCursor(page, 0);
                aux_data = data;
                for (uint8_t line = 0; line < 8; line++)
                {
                        aux_data ^= (toggle << line);
                        for (uint8_t column = 0; column < 128; column++)
                        {
                                oledSendByte(aux_data);
                                _delay_ms(1);
                        }
                        OLED_SetCursor(page, 0);
                }
        }
        return aux_data;
}

uint8_t leftToRight(uint8_t data, uint8_t toggle)
{
        uint8_t aux_data = data;

        for (uint8_t column = 0; column < 128; column++)
        {
                for (uint8_t page = 0; page < 8; page++)
                {
                        OLED_SetCursor(page, column);
                        aux_data = data;
                        for (uint8_t line = 0; line < 8; line++)
                        {
                                aux_data ^= (toggle << line);
                                oledSendByte(aux_data);
                                OLED_SetCursor(page, column);
                                _delay_ms(1);
                        }
                }
        }
        return aux_data;
}
