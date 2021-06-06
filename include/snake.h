#ifndef SNAKE_H
#define SNAKE_H

#include <inttypes.h>

#include "i2c.h"
#include "oled.h"

typedef enum direction_type {
    UP,
    DOWN,
    RIGHT,
    LEFT
}direction;

typedef struct snake_type{
    int size;
    int *head;
    int *tail;

    direction direction;
}snake;

void drawWall();
void drawScore(uint8_t score);

uint8_t topToBottom(uint8_t data, uint8_t toggle);
uint8_t leftToRight(uint8_t data, uint8_t toggle);

void togglePixel(uint8_t line, uint8_t column);
bool checkPixel(uint8_t line, uint8_t column);

void initPixelMatrix();

#endif