#include "controller.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include "oled.h"

void controller_Init() {
        DDRD &= ~(1 << DDD2);
        DDRD &= ~(1 << DDD3);
        DDRD &= ~(1 << DDD4);
        DDRD &= ~(1 << DDD5);

        PCMSK2 |= (1 << PCINT18);
        PCMSK2 |= (1 << PCINT19);
        PCMSK2 |= (1 << PCINT20);
        PCMSK2 |= (1 << PCINT21);
        PCICR |= (1 << PCIE2);

        sei();
}

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