#include "snake.h"

#define TEST_DRAW_BLOCK_FUNCTION 0
#define TEST_SNAKE_MOVEMENT 1

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

#if TEST_SNAKE_MOVEMENT == 1

        snakeHandler = initSnake();
        for (int i = 0; i < snakeHandler.size; i++)
                drawBlock(snakeHandler.body[i].snakeSegment.xCoordinate, snakeHandler.body[i].snakeSegment.yCoordinate, snakeHandler.body[i].snakeSegment.status);

        while (1)
        {

                drawSnake(&snakeHandler, RIGHT);
                _delay_ms(500);

                drawSnake(&snakeHandler, DOWN);
                _delay_ms(500);

                if (snakeHandler.head.snakeSegment.yCoordinate == 30 || snakeHandler.head.snakeSegment.xCoordinate == 10)
                {
                        OLED_Clear(); // clear the doScore()display (for good measure)
                        snakeHandler = initSnake();
                        for (int i = 0; i < snakeHandler.size; i++)
                                drawBlock(snakeHandler.body[i].snakeSegment.xCoordinate, snakeHandler.body[i].snakeSegment.yCoordinate, snakeHandler.body[i].snakeSegment.status);

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