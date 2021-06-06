#ifndef SNAKE_H
#define SNAKE_H

#include <inttypes.h>

#include "i2c.h"
#include "oled.h"

void doWall();
void doScore();
uint8_t topToBottom(uint8_t data, uint8_t toggle);
uint8_t leftToRight(uint8_t data, uint8_t toggle);
void turnOnPixel(uint8_t line, uint8_t column);

#endif