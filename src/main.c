#include "controller.h"
#include "snake.h"

ISR(PCINT2_vect) {
        if (BUTTON_DOWN) {
                OLED_Clear();
                OLED_SetCursor(0, 0);
                OLED_Printf("DOWN PUSHED");
        } else if (BUTTON_LEFT) {
                OLED_Clear();
                OLED_SetCursor(0, 0);
                OLED_Printf("LEFT PUSHED");
        } else if (BUTTON_RIGHT) {
                OLED_Clear();
                OLED_SetCursor(0, 0);
                OLED_Printf("RIGHT PUSHED");
        } else if (BUTTON_UP) {
                OLED_Clear();
                OLED_SetCursor(0, 0);
                OLED_Printf("UP PUSHED");
        } else {
                OLED_Clear();
                OLED_SetCursor(0, 0);
                OLED_Printf("RELEASED");
        }
}

void main() {
        controller_Init();
        OLED_Init();   // initialize the OLED
        OLED_Clear();  // clear the doScore()display (for good measure)
        initPixelMatrix();
        /*
                drawWall(); */
        while (1) {
                /*                 for (uint8_t i = 8; i < 64; i++) {
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
                                } */
        }
}