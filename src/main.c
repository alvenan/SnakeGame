#include "snake.h"

#define TEST_DRAW_BLOCK_FUNCTION 1

int main()
{

        snake snakeHandler = {
            .direction = RIGHT,
            .head = 0,
            .tail = 0,
            .size = 3,

            .draw = &drawSnake,
        };

        snakeHandler.draw(0);

        OLED_Init();  // initialize the OLED
        OLED_Clear(); // clear the doScore()display (for good measure)

#if TEST_DRAW_BLOCK_FUNCTION == 1
        while (1)
        {
                drawBlock(4, 5);
                drawBlock(5, 5);
                drawBlock(5, 6); 
                drawBlock(5, 7);  
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