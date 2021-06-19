#ifndef CONTROLLER_H
#define CONTROLLER_H

#define BUTTON_UP (PIND & (1 << PIND5))
#define BUTTON_DOWN (PIND & (1 << PIND3))
#define BUTTON_RIGHT (PIND & (1 << PIND4))
#define BUTTON_LEFT (PIND & (1 << PIND2))

#define PD2_SET_IN DDRD &= ~(1 << DDD2);
#define PD3_SET_IN DDRD &= ~(1 << DDD3);
#define PD4_SET_IN DDRD &= ~(1 << DDD4);
#define PD5_SET_IN DDRD &= ~(1 << DDD5);

#define TARGET AKKTMEGA_3208

#if TARGET == ATMEGA_3208
        // #define PD2_SET_INT PCMSK2 |= (1 << PCINT18);
        // #define PD3_SET_INT PCMSK2 |= (1 << PCINT19);
        // #define PD4_SET_INT PCMSK2 |= (1 << PCINT20);
        // #define PD5_SET_INT PCMSK2 |= (1 << PCINT21);

        // #define PCINT2_VECT_SET PCICR |= (1 << PCIE2);
        // #define INT_ROUTINE ISR(PCINT2_vect)
#endif




typedef enum buttonDirectionsType
{
        BT_UP,
        BT_DOWN,
        BT_RIGHT,
        BT_LEFT,
        BT_RELEASED
} buttonDirection;

int pressedDirection;

void controller_Init();

#endif