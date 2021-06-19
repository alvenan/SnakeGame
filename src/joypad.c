#include "joypad.h"

#include <avr/interrupt.h>
#include <avr/io.h>

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
        PD0_SET_IN;
        PD0_SET_INT;

        PD1_SET_IN;
        PD1_SET_INT;

        PD2_SET_IN;
        PD2_SET_INT;

        PD3_SET_IN;
        PD3_SET_INT;

        PCINT0_VECT_SET;
        sei();
}
