#include "joypad.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "oled.h"

#include "oled.h"

INT_ROUTINE {
        if (BUTTON_UP) {
                pressedDirection = BT_UP;
                OLED_SetCursor(0, 0);
                OLED_Clear();
                pressedDirection = BT_UP;
                OLED_Printf("UP");
        } else if (BUTTON_DOWN) {
                pressedDirection = BT_DOWN;
                OLED_SetCursor(0, 0);
                OLED_Clear();
                pressedDirection = BT_UP;
                OLED_Printf("DOWN");
        } else if (BUTTON_RIGHT) {
                pressedDirection = BT_RIGHT;
                OLED_SetCursor(0, 0);
                OLED_Clear();
                pressedDirection = BT_UP;
                OLED_Printf("RIGHT");
        } else if (BUTTON_LEFT) {
                pressedDirection = BT_LEFT;
                OLED_SetCursor(0, 0);
                OLED_Clear();
                pressedDirection = BT_UP;
                OLED_Printf("LEFT");
        } else {
                pressedDirection = BT_RELEASED;
                OLED_SetCursor(0, 0);
                OLED_Clear();
                pressedDirection = BT_UP;
                OLED_Printf("RELEASED");
        }
}

void joypad_Init() {
        PB0_SET_IN;
        PB0_SET_INT;

        PB1_SET_IN;
        PB1_SET_INT;

        PB2_SET_IN;
        PB2_SET_INT;

        PB3_SET_IN;
        PB3_SET_INT;

        PCINT0_VECT_SET;
        sei();
}
