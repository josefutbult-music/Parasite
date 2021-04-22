/* 
* Encoder.cpp
*
* Created: 2021-04-22 14:52:13
* Author: josef
*/


#include "Encoder.h"
#include <avr/io.h>
#include<avr/interrupt.h>

#define READ_RATE 0x0f;
#define READ_RATE_DELAYED 0x1000;
#define CLK PINB1
#define DATA PINB2
#define BTN PINB0

int Encoder::increment_val = 0;
uint8_t Encoder::input_state = 0;
int Encoder::buttonpress = 0;

ISR(TIMER3_OVF_vect)
{
	Encoder::on_interrupt();
}

void Encoder::init()
{
	// Set B0, B1 and B2 to inputs
	DDRB &= ~((1 << CLK) | (1 << DATA) | (1 << BTN));
	
	// Set B0 to pullup
	PORTB |= (1 << BTN);
	
	cli();
	TCCR3A = 0x00;
	// Timer mode with 8 prescaler
	TCCR3B = (1 << CS31);
	// Enable timer1 overflow interrupt(TOIE1)
	TIMSK3 = (1 << TOIE3);
	sei();
	
}

int Encoder::get_increment_val()
{
	cli();
	int tmp = Encoder::increment_val;
	Encoder::increment_val = 0;
	sei();
	return tmp;
}

int Encoder::get_buttonpress()
{
	cli();
	int tmp = Encoder::buttonpress;
	Encoder::buttonpress = 0;
	sei();
	return tmp;
}

void Encoder::on_interrupt()
{
	
	uint8_t current_state = PINB;
	
	// Checks if the clk input or button input has changed
	if ((Encoder::input_state & (1 << PINB2)) != (current_state & (1 << PINB2)))
	{
		Encoder::input_state =	(Encoder::input_state & ~(1 << PINB2)) | 
								(current_state & (1 << PINB2));
		// Checks for a rising edge on the clk input
		if (Encoder::input_state & (1 << PINB2))
		{
			// Checks state of the data input
			Encoder::increment_val += (current_state & (1 << PINB1)) ? 1 : -1;
			// Increases the time until next read to prevent debouncing
			TCNT3 = 0xffff - READ_RATE_DELAYED;
			return;
		}
	}
	// Checks for falling edge on button input
	if ((Encoder::input_state & (1 << PINB0)) != (current_state & (1 << PINB0)))
	{
		Encoder::input_state =	(Encoder::input_state & ~(1 << PINB0)) |
								(current_state & (1 << PINB0));
		
		if (!(Encoder::input_state & (1 << PINB0)))
		{
			Encoder::buttonpress++;
			// Increases the time until next read to prevent debouncing
			TCNT3 = 0xffff - READ_RATE_DELAYED;
			return;
		}
	}
	
	// Sets the time until next read
	TCNT3 = 0xffff - READ_RATE;
}