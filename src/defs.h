#ifndef _IO_MACRO_H__
#define _IO_MACRO_H__

typedef struct
{
	unsigned bit0:1;
	unsigned bit1:1;
	unsigned bit2:1;
	unsigned bit3:1;
	unsigned bit4:1;
	unsigned bit5:1;
	unsigned bit6:1;
	unsigned bit7:1;
} BYTE_BITFIELD;

// Data Direction
#define ddra (*((volatile BYTE_BITFIELD*)(&DDRA)))
#define ddrb (*((volatile BYTE_BITFIELD*)(&DDRB)))
#define ddrc (*((volatile BYTE_BITFIELD*)(&DDRC)))
#define ddrd (*((volatile BYTE_BITFIELD*)(&DDRD)))
// Output Port
#define porta (*((volatile BYTE_BITFIELD*)(&PORTA)))
#define portb (*((volatile BYTE_BITFIELD*)(&PORTB)))
#define portc (*((volatile BYTE_BITFIELD*)(&PORTC)))
#define portd (*((volatile BYTE_BITFIELD*)(&PORTD)))
// Input Port
#define pina (*((volatile BYTE_BITFIELD*)(&PINA)))
#define pinb (*((volatile BYTE_BITFIELD*)(&PINB)))
#define pinc (*((volatile BYTE_BITFIELD*)(&PINC)))
#define pind (*((volatile BYTE_BITFIELD*)(&PIND)))


#define Set_bit(y,bit)		(y|=(1<<bit))		// Coloca 1 no bit da variável y
#define Clr_bit(y,bit)		(y&=~(1<<bit))		// Coloca 0 no bit da variável y
#define Cpl_bit(y,bit)		(y^=(1<<bit))		// Troca o estado do bit da variável y
#define Tst_bit(y,bit)		(y&(1<<bit))		// Retorna o estado do bit

#endif
