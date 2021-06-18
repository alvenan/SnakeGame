all : main.o

oled.o : oled.c oled.h
         cc -c oled.c

clean :
        rm edit oled.o
