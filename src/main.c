#include "oled.h"

void main() {
    OLED_Init();   // initialize the OLED
    OLED_Clear();  // clear the doScore()display (for good measure)
    doWall();
    turnOnPixel(55, 10);
    while (1) {
        doScore();
    }
}