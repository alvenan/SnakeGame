#include "joypad.h"
#include "snake.h"
#include <stdio.h>
#include <util/atomic.h>

#define TEST_DRAW_BLOCK_FUNCTION 0
#define TEST_SNAKE_MOVEMENT 1

#define RELEASE_VERSION 1

#define XSTR(x) STR(x)
#define STR(x) #x

#pragma message "The value of ABC: " XSTR(TEST_SNAKE_MOVEMENT)

int qdelay = 20;
int count = 0;

int foodDelay = 0;
int delay = 0;
volatile int pressedDirection = BT_RELEASED;

int main()
{
        snake snakeHandler = {0};

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

        initSnake(&snakeHandler);
        drawWall();

        for (int i = 0; i < snakeHandler.size; i++)
        {
                drawBlock(snakeHandler.body[i].snakeSegment.xCoordinate, snakeHandler.body[i].snakeSegment.yCoordinate, snakeHandler.body[i].snakeSegment.status);
                _delay_ms(500);
        }

#if RELEASE_VERSION == 1

        //joypad_Init();
#endif

        for (;;)
        {
#if RELEASE_VERSION == 1
                if (pressedDirection != BT_RELEASED)
                {
                        drawSnake(&snakeHandler, pressedDirection);
                        pressedDirection = BT_RELEASED;
                }
                else
                {
                        drawSnake(&snakeHandler, snakeHandler.direction);
                }
                // if (foodDelay == 50)
                // {
                //         drawFood();
                //         foodDelay = 0;
                // }
                // else
                // {
                //         foodDelay++;
                // }

                _delay_ms(200);

#else
                int steps;

                // initSnake(&snakeHandler);
                // drawWall();

                // for (int i = 0; i < snakeHandler.size; i++)
                // {
                //         drawBlock(snakeHandler.body[i].snakeSegment.xCoordinate, snakeHandler.body[i].snakeSegment.yCoordinate, snakeHandler.body[i].snakeSegment.status);
                //         _delay_ms(500);
                // }
#if CYCLE_MOVE_TEST == 1
                drawSnake(&snakeHandler, RIGHT);
                _delay_ms(200);

                drawSnake(&snakeHandler, DOWN);
                _delay_ms(200);

                drawSnake(&snakeHandler, LEFT);
                _delay_ms(200);

                drawSnake(&snakeHandler, UP);
                _delay_ms(200);
#endif
                if (count == 2)
                {
                        drawFood();
                        count = 0;
                }
                else
                {
                        count++;
                }

                drawSnake(&snakeHandler, RIGHT);
                _delay_ms(delay);

                drawSnake(&snakeHandler, RIGHT);
                _delay_ms(delay);

                drawSnake(&snakeHandler, RIGHT);
                _delay_ms(delay);

                drawSnake(&snakeHandler, RIGHT);
                _delay_ms(delay);

                drawSnake(&snakeHandler, DOWN);
                _delay_ms(delay);

                drawSnake(&snakeHandler, DOWN);
                _delay_ms(delay);

                drawSnake(&snakeHandler, DOWN);
                _delay_ms(delay);

                drawSnake(&snakeHandler, DOWN);
                _delay_ms(delay);

                for (steps = 0; steps < 14; steps++)
                {
                        drawSnake(&snakeHandler, LEFT);
                        _delay_ms(delay);
                }

                for (steps = 0; steps < 4; steps++)
                {
                        drawSnake(&snakeHandler, UP);
                        _delay_ms(delay);
                }

                for (steps = 0; steps < 10; steps++)
                {
                        drawSnake(&snakeHandler, RIGHT);
                        _delay_ms(delay);
                }
                // if (snakeHandler.head.snakeSegment.yCoordinate == 15 || snakeHandler.head.snakeSegment.xCoordinate == 5)
                // {
                // OLED_Clear(); // clear the doScore()display (for good measure)
                // drawWall();

                //snakeHandler = initSnake();
                // for (int i = 0; i < snakeHandler.size; i++)
                // {
                //         // OLED_Printf("x %d y %d", snakeHandler.body[i].snakeSegment.xCoordinate, snakeHandler.body[i].snakeSegment.yCoordinate);
                //         drawBlock(snakeHandler.body[i].snakeSegment.xCoordinate, snakeHandler.body[i].snakeSegment.yCoordinate, snakeHandler.body[i].snakeSegment.status);
                //         _delay_ms(500);
                // }

                // _delay_ms(500);
                // }
#endif
        }
        return 0;
}