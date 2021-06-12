#ifndef SNAKE_H
#define SNAKE_H

#include <inttypes.h>

#include "i2c.h"
#include "oled.h"

#define PAGE0 0
#define PAGE7 7

#define UP_WALL_BIT     0x01
#define UP_WALL_PAGE    PAGE0

#define DOWN_WALL_BIT   0x80
#define DOWN_WALL_PAGE  PAGE7

#define LEFT_WALL       0
#define RIGHT_WALL      127

#define SET_BLOCK_MASK(BLOCK_X_POS) ((BLOCK_X_POS%2 == 0)? 0x0F : 0xF0)

typedef enum blockStatusType {
    EMPTY_BLOCK,
    FULL_BLOCK,
    UNKOWN_BLOCK
}blockStatus;

typedef enum snakeDirectionType {
    UP,
    DOWN,
    RIGHT,
    LEFT
}snakeDirection;

typedef struct pixelType{
    uint8_t page;
    uint8_t bit;
    uint8_t segment;
}pixel;

typedef struct blockType{
    uint8_t xCoordinate;
    uint8_t yCoordinate;
    blockStatus status;
}block;

typedef struct snakeBodyType snakeBody;

struct snakeBodyType{
    block snakeSegment;
    snakeBody *next;
};

typedef struct snakeType{
    int size;
    snakeBody head;
    snakeBody tail;

    snakeBody body[SCREEN_TOTAL_BLOCKS];
    snakeDirection direction;
}snake;


void drawBlock(uint8_t x_coordinate, uint8_t y_coordinate, blockStatus blockTypeToDraw);
void drawWall();
void drawScore(uint8_t score);
void drawFood();
int drawSnake(snake *s, snakeDirection dir);
snake initSnake(void);
void drawEmptyBlock();

uint8_t topToBottom(uint8_t data, uint8_t toggle);
uint8_t leftToRight(uint8_t data, uint8_t toggle);

void togglePixel(uint8_t line, uint8_t column);
bool checkPixel(uint8_t line, uint8_t column);

void initPixelMatrix();


void onUserInput();



#endif