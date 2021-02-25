#include "Encoder.h"
#include <avr/io.h>
#include<avr/interrupt.h>

static int increment_val;

ISR(INT1_vect)
{
	increment_val++;
}

void Encoder::init()
{
	cli();
	// Set B1 and B2 to inputs
	DDRB &= ~((1 << DDRB1) | (1 << DDRB2));
	
	// Enable interrupt 1 on falling and rising edges
	EICRA |= (1 << ISC10);
	EIMSK |= (1 << INT1);
	sei();
}

int Encoder::get_increment_val()
{
	cli();
	int tmp = increment_val;
	increment_val = 0;
	sei();
	return tmp;
}