#ifndef CONTROLLER_H
#define CONTROLLER_H


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

typedef enum buttonDirectionsType {
        BT_UP,
        BT_DOWN,
        BT_RIGHT,
        BT_LEFT,
        BT_RELEASED
} buttonDirection;

int pressedDirection;

void controller_Init();

#endif