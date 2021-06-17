#ifndef CONTROLLER_H
#define CONTROLLER_H

#define BUTTON_LEFT (PIND & (1 << PIND2))
#define BUTTON_DOWN (PIND & (1 << PIND3))
#define BUTTON_RIGHT (PIND & (1 << PIND4))
#define BUTTON_UP (PIND & (1 << PIND5))

void controller_Init();

#endif