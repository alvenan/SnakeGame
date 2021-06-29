#ifndef JOYPAD_H
#define JOYPAD_H

#include <avr/io.h>
#include <avr/interrupt.h>

// #include <avr/iom32u4.h>

#include "oled.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "oled.h"

#define BUTTON_LEFT (PINB & (1 << PINB0))
#define BUTTON_DOWN (PINB & (1 << PINB1))
#define BUTTON_RIGHT (PINB & (1 << PINB2))
#define BUTTON_UP (PINB & (1 << PINB3))

#define PB0_SET_IN DDRB &= ~(1 << DDB0);
#define PB1_SET_IN DDRB &= ~(1 << DDB1);
#define PB2_SET_IN DDRB &= ~(1 << DDB2);
#define PB3_SET_IN DDRB &= ~(1 << DDB3);

#define PB0_SET_INT PCMSK0 |= (1 << PCINT0);
#define PB1_SET_INT PCMSK0 |= (1 << PCINT1);
#define PB2_SET_INT PCMSK0 |= (1 << PCINT2);
#define PB3_SET_INT PCMSK0 |= (1 << PCINT3);

#define PCINT0_VECT_SET PCICR |= (1 << PCIE0);

#define INT_ROUTINE ISR(PCINT0_vect)




typedef enum buttonDirectionsType
{
        BT_UP,
        BT_DOWN,
        BT_RIGHT,
        BT_LEFT,
        BT_RELEASED
} buttonDirection;

extern volatile int pressedDirection;

void joypad_Init();

#endif