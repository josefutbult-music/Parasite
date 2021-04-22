#define READ_RATE 100

#include "Controller.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include "../Display/Display.h"

uint16_t Controller::controller_vals[CONTROLLER_LENGTH] = { 0 };
const int Controller::input_map[6] = {0, 1, 2, 3, 4, 5};
uint8_t Controller::controller_vals_changed = 0;
int Controller::current_controller = 0;

void Controller::init()
{
	uint8_t digital_controller_map = 0;
	uint8_t analog_controller_map = 0;
	
	for(int i = 0; i < CONTROLLER_LENGTH; i++){
		switch (controller_map[i].type){
			case DIGITAL_CONTROLLER:
				digital_controller_map |= (1 << Controller::input_map[i]);
			break;
			case ANALOG_CONTROLLER:
				analog_controller_map |= (1 << Controller::input_map[i]);
			break;
			default:
			break;
		}
	}
	
	Controller::init_adc(analog_controller_map);
	Controller::init_digital(digital_controller_map);
	
	Controller::setup_read();
}

void Controller::init_adc(uint8_t analog_controller_map)
{
	// Set bits to input in DDRC
	DDRC &= ~analog_controller_map;
	
	// Disable digital input for all bits in the analog map in DDRC
	DIDR0 |= analog_controller_map;
	
	// Enable ADC and the ADC interrupt
	ADCSRA |= (1 << ADEN) | (1 << ADIE);
	
	// Set ADC prescaler to 128
	ADCSRA |= 0b111;
	
	// Set analog reference to AVCC
	ADMUX |= 1 << REFS0;
}

void Controller::init_digital(uint8_t digital_controller_map)
{
	// Set bits to input in DDRC
	DDRC &= ~digital_controller_map;
	
	cli();
	// Set interrupt to trigger after READ_RATE cycles
	// TCNT2 = READ_RATE;
	TCCR2A = 0x00;
	// Enable timer mode with 256 prescaler
	TCCR2B = (1 << CS22) | (1 << CS21);
	// Disable timer2 overflow interrupt(TOIE2)
	TIMSK2 = (1 << TOIE2);
	sei();
}

void Controller::update_controller_val(uint16_t val)
{
	if(controller_map[Controller::current_controller].type != ANALOG_CONTROLLER || 
		abs(Controller::controller_vals[Controller::current_controller] - val) > ANALOG_THRESHOLD){
		if(Controller::controller_vals[Controller::current_controller] != val){
			Controller::controller_vals_changed |= 1 << Controller::current_controller;
		}
		Controller::controller_vals[Controller::current_controller] = val;
	}
	
}

void Controller::clear_controller_vals_changed()
{
	Controller::controller_vals_changed = 0;
}

uint8_t Controller::get_controller_vals_changed()
{
	return Controller::controller_vals_changed;
}

void Controller::read()
{
	if(controller_map[Controller::current_controller].type == ANALOG_CONTROLLER){
		// Store values in ADC register (Make sure to read ADCL first, to enable change in ADCH. See page 219 in datasheet)
		Controller::update_controller_val(ADCL | (ADCH << 8));
	}
	else if(controller_map[Controller::current_controller].type == DIGITAL_CONTROLLER){
		Controller::update_controller_val((PINC & (1 << Controller::input_map[Controller::current_controller])) ? 1 : 0);
	}
}

void Controller::setup_read(){
	if(controller_map[Controller::current_controller].type == ANALOG_CONTROLLER){
		// Select input to ADC
		ADMUX = (ADMUX & 0xf0) | (Controller::input_map[Controller::current_controller] & 0xf);
		
		// Start conversion
		ADCSRA |= 1 << ADSC;
	}
	else if(controller_map[Controller::current_controller].type == DIGITAL_CONTROLLER){
		// Enable timer2 overflow interrupt(TOIE2)
		TIMSK2 |= (1 << TOIE2);
		// Reset timer2
		TCNT2 = 0;
	}
}

ISR(ADC_vect)
{
	Controller::callback();
}

ISR(TIMER2_OVF_vect)
{
	Controller::callback();
}

// int i = 0;
void Controller::callback()
{
	// Disable timer2 overflow interrupt(TOIE2)
	TIMSK2 &= ~(1 << TOIE2);
	// Display::set_disp_val(i++);
	
	Controller::read();
	Controller::current_controller = (Controller::current_controller + 1) % CONTROLLER_LENGTH;
	Controller::setup_read();
}

 uint16_t Controller::get_controller_val(int index)
 {
	 if(index >= 0 && index < CONTROLLER_LENGTH){
		 return Controller::controller_vals[index];
	 }
	 else {
		 return -1;
	 }
 }