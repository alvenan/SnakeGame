#include "joypad.h"

#include <avr/interrupt.h>
#include <avr/io.h>

INT_ROUTINE {
        if (BUTTON_UP) {
                pressedDirection = BT_UP;
        } else if (BUTTON_DOWN) {
                pressedDirection = BT_DOWN;
        } else if (BUTTON_RIGHT) {
                pressedDirection = BT_RIGHT;
        } else if (BUTTON_LEFT) {
                pressedDirection = BT_LEFT;
        } else {
                pressedDirection = BT_RELEASED;
        }
}

void joypad_Init() {
        PD2_SET_IN;
        PD2_SET_INT;

        PD3_SET_IN;
        PD3_SET_INT;

        PD4_SET_IN;
        PD4_SET_INT;

        PD5_SET_IN;
        PD5_SET_INT;

        PCINT2_VECT_SET;
        sei();
}
