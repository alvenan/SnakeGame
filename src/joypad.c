#include "joypad.h"

volatile int pressedDirection = BT_RELEASED;

ISR(PCINT0_vect) {
    //@todo change to switch case
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
