SNAKE_GAME_SOURCE_PATH  = src
SNAKE_GAME_INCLUDE_PATH = include

AVR_INCLUDE_PATH = /include
all : main.o
		
main.o : oled.o snake.o
		avr-gcc -c $(SNAKE_GAME_SOURCE_PATH)/main.c -I$(SNAKE_GAME_INCLUDE_PATH)

oled.o : $(SNAKE_GAME_SOURCE_PATH)/oled.c $(SNAKE_GAME_INCLUDE_PATH)/oled.h
		avr-gcc -c $(SNAKE_GAME_SOURCE_PATH)/oled.c -I$(AVR_INCLUDE_PATH) -I$(SNAKE_GAME_INCLUDE_PATH)

snake.o: $(SNAKE_GAME_SOURCE_PATH)/snake.c $(SNAKE_GAME_INCLUDE_PATH)/snake.h
		avr-gcc -c $(SNAKE_GAME_SOURCE_PATH)/snake.c -I$(AVR_INCLUDE_PATH) -I$(SNAKE_GAME_INCLUDE_PATH)		

clean:
		rm ./*.o
