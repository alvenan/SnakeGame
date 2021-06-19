#include "snake.h"
#include "string.h"

uint8_t pixel_matrix[8][128]; // Matrix
uint8_t page_line[2];         // [0] -> page; [1] -> line

//@TODO change to use
/*
vector[max_col_inside_game_area]
bitmask will define which line
status = vector[col] & (1<<bitmask)

*/
blockStatus blockField[40 / BLOCK_SIDE_TOTAL_PIXELS][120 / BLOCK_SIDE_TOTAL_PIXELS] = {EMPTY_BLOCK}; //limits 52/4 and 126/4 @TODO change this to use MACROS instead numbers

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

static uint8_t convertBlockXCoordinateToLine(uint8_t blockXPosition)
{
        return ((blockXPosition * BLOCK_SIDE_TOTAL_PIXELS) + 17);
}

static uint8_t convertBlockYCoordinateToColumn(uint8_t blockYPosition)
{
        return (blockYPosition * BLOCK_SIDE_TOTAL_PIXELS) + 4;
}

static uint8_t convertLineToPage(uint8_t line)
{
        return (line / 8);
}

static uint8_t convertLineToBitPosition(uint8_t line)
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

void increaseSnakeBody()
{
}

snake initSnake(void)
{
        snake s;

        s.size = 3;
        s.direction = RIGHT;

        s.head.snakeSegment.xCoordinate = 0;
        s.head.snakeSegment.yCoordinate = 10;
        s.head.snakeSegment.status = FULL_BLOCK;
        s.head.next = &s.body[1];

        s.tail.snakeSegment.xCoordinate = 0;
        s.tail.snakeSegment.yCoordinate = 10 - (s.size - 1);
        s.tail.snakeSegment.status = FULL_BLOCK;
        s.tail.next = NULL;

        s.body[0] = s.head;

        for (int i = 1; i < (s.size - 1); i++)
        {
                s.body[i].snakeSegment.xCoordinate = 0;
                s.body[i].snakeSegment.yCoordinate = (10 - i);
                s.body[i].snakeSegment.status = FULL_BLOCK;
        }

        s.body[s.size - 1] = s.tail;

        memset(blockField, 0, sizeof(blockField));

        return s;
}

blockStatus checkBlockStatus(int blockXPosition, int blockYPosition)
{
        if ((blockXPosition < (40 / BLOCK_SIDE_TOTAL_PIXELS)) && (blockYPosition < (120 / BLOCK_SIDE_TOTAL_PIXELS)))
        {

                if (blockField[blockXPosition][blockYPosition] == FULL_BLOCK)
                {
                        return FULL_BLOCK;
                }
                else if (blockField[blockXPosition][blockYPosition] == EMPTY_BLOCK)
                {
                        return EMPTY_BLOCK;
                }
                else
                        return UNKOWN_BLOCK;
        }
        else
        {
                OLED_Printf("GAME OVER");
                return UNKOWN_BLOCK;
        }
}

//MAYBE CHANGE TO insertBlock
void drawBlock(uint8_t blockXPosition, uint8_t blockYPosition, blockStatus blockTypeToDraw)
{
        //@TODO: function to draw a block at screen

        //first check if block have valid position
        //second check if block position is validq

        uint8_t line = convertBlockXCoordinateToLine(blockXPosition);
        uint8_t col = convertBlockYCoordinateToColumn(blockYPosition);
        uint8_t blockMask = SET_BLOCK_MASK(blockXPosition);

        if (blockTypeToDraw == FULL_BLOCK)
        {

                if (checkBlockStatus(blockXPosition, blockYPosition) == EMPTY_BLOCK)
                {

                        //@TODO move both if checks and all code to another function, and just call this function here

                                if (blockField[blockXPosition + 1][blockYPosition] == EMPTY_BLOCK)
                                {
                                        //write 0x0F
                                        for (int i = 0; i < BLOCK_SIDE_TOTAL_PIXELS; i++)
                                        {
                                                OLED_SetCursor(convertLineToPage(line), col + i);
                                                oledSendByte(0xFF);
                                        }

                                        blockField[blockXPosition][blockYPosition] = FULL_BLOCK;
                                }
                                else if (blockField[blockXPosition + 1][blockYPosition] == FULL_BLOCK)
                                {
                                        for (int i = 0; i < BLOCK_SIDE_TOTAL_PIXELS; i++)
                                        {
                                                OLED_SetCursor(convertLineToPage(line), col + i);
                                                oledSendByte(0XFF);
                                        }

                                        blockField[blockXPosition][blockYPosition] = FULL_BLOCK;
                                }

 
                        
                }

                else
                {
                        //error
                        OLED_Clear();
                }
        }
        else if (blockTypeToDraw == EMPTY_BLOCK)
        {
                if (blockMask == 0x0F)
                {
                        if (blockField[blockXPosition + 1][blockYPosition] == EMPTY_BLOCK)
                        {
                                for (int i = 0; i < BLOCK_SIDE_TOTAL_PIXELS; i++)
                                {
                                        OLED_SetCursor(convertLineToPage(line), col + i);
                                        oledSendByte(0X00);
                                }

                                blockField[blockXPosition][blockYPosition] = EMPTY_BLOCK;
                        }
                        else if (blockField[blockXPosition + 1][blockYPosition] == FULL_BLOCK)
                        {
                                for (int i = 0; i < BLOCK_SIDE_TOTAL_PIXELS; i++)
                                {
                                        OLED_SetCursor(convertLineToPage(line), col + i);
                                        oledSendByte(0X00);
                                }

                                blockField[blockXPosition][blockYPosition] = EMPTY_BLOCK;
                        }
                }

                if (blockMask == 0xF0)
                {
                        if (blockField[blockXPosition - 1][blockYPosition] == EMPTY_BLOCK)
                        {
                                for (int i = 0; i < BLOCK_SIDE_TOTAL_PIXELS; i++)
                                {
                                        OLED_SetCursor(convertLineToPage(line), col + i);
                                        oledSendByte(0X00);
                                }

                                blockField[blockXPosition][blockYPosition] = EMPTY_BLOCK;
                        }
                        else if (blockField[blockXPosition - 1][blockYPosition] == FULL_BLOCK)
                        {
                                for (int i = 0; i < BLOCK_SIDE_TOTAL_PIXELS; i++)
                                {
                                        OLED_SetCursor(convertLineToPage(line), col + i);
                                        oledSendByte(0X00);
                                }

                                blockField[blockXPosition][blockYPosition] = EMPTY_BLOCK;
                        }
                }
        }
}

void drawFood(snakeDirection dir) {
        //@TODO: function to randomize which position food will appear
        return 0;
}

int drawSnake(snake *s, snakeDirection dir)
{
        int delay_ms = 10;
        //@TODO check limits of array
        snakeBody temp = s->body[s->size - 2];
        snakeBody aux;

        snakeBody currentTail = s->tail;
        snakeBody currentHead = s->head;

        for (int i = 2; i < (s->size - 1); i++)
        {
                aux = s->body[i - 1];
                //@TODO change this to memcpy?
                s->body[i].snakeSegment = aux.snakeSegment;
                s->body[i].next = aux.next;
        }

        s->body[1].snakeSegment = s->head.snakeSegment;

        //@TODO: function to update snake draw at display
        if (s->direction == dir)
        {
                switch (dir)
                {
                case (RIGHT):

                        // s->body[1].snakeSegment = s->head.snakeSegment;

                        s->head.snakeSegment.yCoordinate = s->head.snakeSegment.yCoordinate + 1;
                        s->body[0] = s->head;

                        drawBlock(s->head.snakeSegment.xCoordinate, s->head.snakeSegment.yCoordinate, FULL_BLOCK);
                        _delay_ms(delay_ms);
                        //drawBlock(s->head.snakeSegment.xCoordinate, s->head.snakeSegment.yCoordinate, EMPTY_BLOCK);
                        drawBlock(s->tail.snakeSegment.xCoordinate, s->tail.snakeSegment.yCoordinate, EMPTY_BLOCK);

                        // s->tail.snakeSegment.yCoordinate = s->tail.snakeSegment.yCoordinate + 1;
                        s->tail.snakeSegment = temp.snakeSegment;
                        // s->tail.next = &s->body[s->size-2];
                        s->body[s->size - 1] = s->tail;

                        break;
                case (DOWN):
                        // s->body[1].snakeSegment = s->head.snakeSegment;

                        s->head.snakeSegment.xCoordinate = s->head.snakeSegment.xCoordinate + 1;
                        s->body[0] = s->head;

                        drawBlock(s->head.snakeSegment.xCoordinate, s->head.snakeSegment.yCoordinate, FULL_BLOCK);
                        _delay_ms(delay_ms);
                        //drawBlock(s->head.snakeSegment.xCoordinate, s->head.snakeSegment.yCoordinate, EMPTY_BLOCK);
                        drawBlock(s->tail.snakeSegment.xCoordinate, s->tail.snakeSegment.yCoordinate, EMPTY_BLOCK);

                        // s->tail.snakeSegment.yCoordinate = s->tail.snakeSegment.yCoordinate + 1;
                        // s->tail = s->tail.next;
                        s->tail.snakeSegment = temp.snakeSegment;
                        // s->tail.next = &s->body[s->size-2];
                        s->body[s->size - 1] = s->tail;

                        break;

                default:
                        break;
                }
        }
        else
        {

                switch (dir)
                {
                case (DOWN):
                        // s->body[1].snakeSegment = s->head.snakeSegment;

                        s->head.snakeSegment.xCoordinate = s->head.snakeSegment.xCoordinate + 1;
                        s->body[0] = s->head;

                        drawBlock(s->head.snakeSegment.xCoordinate, s->head.snakeSegment.yCoordinate, FULL_BLOCK);
                        _delay_ms(delay_ms);
                        //drawBlock(s->head.snakeSegment.xCoordinate, s->head.snakeSegment.yCoordinate, EMPTY_BLOCK);
                        drawBlock(s->tail.snakeSegment.xCoordinate, s->tail.snakeSegment.yCoordinate, EMPTY_BLOCK);

                        // s->tail.snakeSegment.yCoordinate = s->tail.snakeSegment.yCoordinate + 1;

                        s->tail.snakeSegment = temp.snakeSegment;
                        // s->tail.next = &s->body[s->size-2];
                        s->body[s->size - 1] = s->tail;

                        break;

                default:
                        break;
                }
        }
        return 0;
}

void drawWall()
{
        for (uint8_t page = 1; page < 8; page++)
        {
                OLED_SetCursor(page, 0);
                for (uint8_t column = 0; column < 128; column++)
                {
                        if ((column == 4) || (column == 123))
                        {
                                if (page == 1)
                                {
                                        pixel_matrix[page][column] = 0x80;
                                        oledSendByte(0x80);
                                }
                                else if (page == 7)
                                {
                                        pixel_matrix[page][column] = 0x01;
                                        oledSendByte(0x01);
                                }
                                else
                                {
                                        pixel_matrix[page][column] = 0xFF;
                                        oledSendByte(0xFF);
                                }
                        }
                        else if ((page == 1) && column > 3 && (column < 124))
                        {
                                pixel_matrix[page][column] = 0x80;
                                oledSendByte(0x80);
                        }
                        else if ((page == 7) && (column > 3) && (column < 124))
                        {
                                pixel_matrix[page][column] = 0x01;
                                oledSendByte(0x01);
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
