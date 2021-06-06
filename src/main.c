#include "snake.h"

void main() {
        OLED_Init();   // initialize the OLED
        OLED_Clear();  // clear the doScore()display (for good measure)
        initPixelMatrix();

        while (1) {
                for (uint8_t i = 0; i < 64; i++) {
                        for (uint8_t j = 0; j < 128; j++) {
                                togglePixel(i, j);
                                togglePixel(i, j + 1);
                                togglePixel(i + 1, j);
                                togglePixel(i + 1, j + 1);
                                _delay_ms(10);
                                OLED_Clear()
                        }
                }
        }

        /*     doWall();
            while (1) {
                doScore();
            } */
}