#include "snake.h"
uint8_t pixel_matrix[8][128];  // Matrix
uint8_t page_line[2];          // [0] -> page; [1] -> line

void initPixelMatrix() {
        for (uint8_t page = 0; page < 8; page++) {
                for (uint8_t column = 0; column < 128; column++) {
                        pixel_matrix[page][column] = 0x00;
                }
        }
}

void doWall() {
        for (uint8_t page = 1; page < 8; page++) {
                OLED_SetCursor(page, 0);
                for (uint8_t column = 0; column < 128; column++) {
                        if ((column == 0) || (column == 127)) {
                                pixel_matrix[page][column] = 0xFF;
                                oledSendByte(0xFF);
                        } else if (page == 1) {
                                pixel_matrix[page][column] = 0x01;
                                oledSendByte(0x01);
                        } else if (page == 7) {
                                pixel_matrix[page][column] = 0x80;
                                oledSendByte(0x80);
                        } else {
                                pixel_matrix[page][column] = 0x00;
                                oledSendByte(0x00);
                        }
                }
        }
}

bool checkPixel(uint8_t line, uint8_t column) {
        uint8_t mask = 0x00;
        updatePageLine(line);
        mask = 1 << page_line[1];
        return ((pixel_matrix[page_line[0]][column] & mask) !=
                0);  // -> return 0 if the pixel is OFF, return 1 if ti is ON
}

void updatePageLine(uint8_t line) {
        page_line[0] = 0x00;
        page_line[1] = 0x00;

        page_line[1] = line % 8;                   // pixel line in the page
        page_line[0] = (line - page_line[1]) / 8;  // page
}

void doScore() {
        for (uint16_t score = 0x0000; score < 0xFFFF; score++) {
                OLED_SetCursor(0, 0);
                OLED_Printf("%u", score);
                _delay_ms(100);
        }
}

uint8_t topToBottom(uint8_t data, uint8_t toggle) {
        uint8_t aux_data = data;
        for (uint8_t page = 0; page < 8; page++) {
                OLED_SetCursor(page, 0);
                aux_data = data;
                for (uint8_t line = 0; line < 8; line++) {
                        aux_data ^= (toggle << line);
                        for (uint8_t column = 0; column < 128; column++) {
                                oledSendByte(aux_data);
                                _delay_ms(1);
                        }
                        OLED_SetCursor(page, 0);
                }
        }
        return aux_data;
}

uint8_t leftToRight(uint8_t data, uint8_t toggle) {
        uint8_t aux_data = data;

        for (uint8_t column = 0; column < 128; column++) {
                for (uint8_t page = 0; page < 8; page++) {
                        OLED_SetCursor(page, column);
                        aux_data = data;
                        for (uint8_t line = 0; line < 8; line++) {
                                aux_data ^= (toggle << line);
                                oledSendByte(aux_data);
                                OLED_SetCursor(page, column);
                                _delay_ms(1);
                        }
                }
        }
        return aux_data;
}

void togglePixel(uint8_t line, uint8_t column) {
        uint8_t page, page_line;
        page_line = line % 8;
        page = (line - page_line) / 8;
        OLED_SetCursor(page, column);

        pixel_matrix[page][column] ^= (1 << page_line);
        oledSendByte(pixel_matrix[page][column]);
}