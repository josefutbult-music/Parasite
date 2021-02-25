#include "Display.h"
#include <avr/io.h>
#include<avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>

#define DISP_SEL_0 2
#define DISP_SEL_1 3

#define FRAMERATE 256

uint16_t Display::out_value = 0;

ISR(TIMER1_OVF_vect)
{
	PORTE ^= (1 << DISP_SEL_0) | (1 << DISP_SEL_1);
	PORTD = (PORTE & (1 << DISP_SEL_0) ? (Display::out_value >> 8): Display::out_value) & 0xff;
}

void Display::init()
{
	Display::out_value = 0xffff;
	// Set display select 0 and 1 to high
	DDRE |= (1 << DISP_SEL_0) | (1 << DISP_SEL_1);
	PORTE |= (1 << DISP_SEL_1);
	
	// Set all display characters to 0
	DDRD = 0xff;
	PORTD = 0xff;
	
	cli();
	TCCR1A = 0x00;
	// Timer mode with no prescaler
	TCCR1B = (1<<CS10);
	// Enable timer1 overflow interrupt(TOIE1)
	TIMSK1 = (1 << TOIE1);
	sei();
}

uint8_t Display::generate_digit(uint8_t value)
{
	switch(value){
		case 0:
		return 0b11000000;
		
		case 1:
		return 0b11101101;
		
		case 2:
		return 0b10110000;
		
		case 3:
		return 0b10100100;
		
		case 4:
		return 0b10001101;
		
		case 5:
		return 0b10000110;
		
		case 6:
		return 0b10000010;
		
		case 7:
		return 0b11101100;
		
		case 8:
		return 0b10000000;
		
		case 9:
		return 0b10000100;
		
		default:
		return 0b11111111;
	}
}

void Display::set_disp_val(uint8_t value)
{
	uint16_t tmp = value <= 99 ? (generate_digit(value / 10) << 8) | generate_digit(value % 10) : 0xbfbf;	
	cli();
	Display::out_value = tmp;
	sei();
}