#include "controller.h"

#include <avr/interrupt.h>
#include <avr/io.h>

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