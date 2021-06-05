#include "oled.h"

void main() {
    uint8_t data = 0x00;
    uint8_t v1 = 1, v2 = 0;
    OLED_Init();   // initialize the OLED
    OLED_Clear();  // clear the display (for good measure)
    while (1) {
        for (uint8_t page = 0; page < 8; page++) {
            OLED_SetCursor(page, 0);
            data = v2;
            for (uint8_t line = 0; line < 8; line++) {
                data ^= (v1 << line);
                for (uint8_t column = 0; column < 128; column++) {
                    oledSendByte(data);
                    _delay_ms(1);
                }
                OLED_SetCursor(page, 0);
            }
        }
        v1 == 1 ? 0 : 1;
        v2 = data;
    }
}