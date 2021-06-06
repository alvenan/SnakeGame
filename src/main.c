#include "snake.h"

void main() {
        OLED_Init();   // initialize the OLED
        OLED_Clear();  // clear the doScore()display (for good measure)
        initPixelMatrix();

        int score = 0;

        doWall();
        while (1) {
                for (uint8_t i = 8; i < 64; i++) {
                        doScore(score);
                        for (uint8_t j = 1; j < 127; j++) {
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
}