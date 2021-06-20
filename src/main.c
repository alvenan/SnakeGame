#include "joypad.h"
#include "snake.h"

#include <stdio.h>
#include <util/atomic.h>
#define TEST_DRAW_BLOCK_FUNCTION 0
#define TEST_SNAKE_MOVEMENT 1

#define XSTR(x) STR(x)
#define STR(x) #x

#pragma message "The value of ABC: " XSTR(TEST_SNAKE_MOVEMENT)

int main()
{
        snake snakeHandler = {0};
        // joypad_Init();
        OLED_Init();  // initialize the OLED
        OLED_Clear(); // clear the doScore()display (for good measure)

#if TEST_DRAW_BLOCK_FUNCTION == 1
        while (1)
        {
                drawBlock(4, 5, FULL_BLOCK);
                drawBlock(5, 5, FULL_BLOCK);
                drawBlock(5, 6, FULL_BLOCK);
                drawBlock(5, 7, FULL_BLOCK);
                _delay_ms(500);

                drawBlock(4, 5, EMPTY_BLOCK);
                drawBlock(5, 8, FULL_BLOCK);
                _delay_ms(500);
        }
#endif

#if TEST_SNAKE_MOVEMENT == 1

        //drawWall();

        joypad_Init();
        //sei();
        for (;;)
        {
                cli();

                if (pressedDirection == 10)
                {
                        OLED_Printf("WORKING!!!!!");
                }
                else
                {
                        OLED_Printf("ERROR");
                }
                sei();
        }


//         while(1){
// //                 ATOMIC_BLOCK(ATOMIC_FORCEON)
// // {
// //         //       drawWall();
// //                }
//                 // if(x ==10)
//                 //         OLED_Printf("ISR");
//                 // else
//                 //         OLED_Printf("ERROR");
//               //OLED_Printf("dEBUG: %d", BUTTON_DOWN);
//         }

snakeHandler = initSnake();
drawWall();

for (int i = 0; i < snakeHandler.size; i++)
{
        drawBlock(snakeHandler.body[i].snakeSegment.xCoordinate, snakeHandler.body[i].snakeSegment.yCoordinate, snakeHandler.body[i].snakeSegment.status);
        _delay_ms(500);
}

while (1)
{

        drawSnake(&snakeHandler, RIGHT);
        _delay_ms(200);

        drawSnake(&snakeHandler, DOWN);
        _delay_ms(200);

        if (snakeHandler.head.snakeSegment.yCoordinate == 15 || snakeHandler.head.snakeSegment.xCoordinate == 5)
        {
                OLED_Clear(); // clear the doScore()display (for good measure)
                drawWall();

                snakeHandler = initSnake();
                for (int i = 0; i < snakeHandler.size; i++)
                {
                        // OLED_Printf("x %d y %d", snakeHandler.body[i].snakeSegment.xCoordinate, snakeHandler.body[i].snakeSegment.yCoordinate);
                        drawBlock(snakeHandler.body[i].snakeSegment.xCoordinate, snakeHandler.body[i].snakeSegment.yCoordinate, snakeHandler.body[i].snakeSegment.status);
                        _delay_ms(500);
                }

                _delay_ms(500);
        }
}
#endif
initPixelMatrix();

int score = 0;

drawWall();
while (1)
{
        for (uint8_t i = 8; i < 64; i++)
        {
                drawScore(score);
                for (uint8_t j = 1; j < 127; j++)
                {
                        togglePixel(i, j);
                        togglePixel(i, j + 1);
                        togglePixel(i + 1, j);
                        togglePixel(i + 1, j + 1);
                        _delay_ms(10);
                        togglePixel(i, j);
                        togglePixel(i, j + 1);
                        togglePixel(i + 1, j);
                        togglePixel(i + 1, j + 1);
                }
                score += 1;
        }
}
return 0;
}