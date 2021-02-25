#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <avr/io.h>
#include <stdint.h>

#include "Controller_Map.h"

class Controller
{
public:
	static void init();
	static uint16_t get_controller_val(int index);
	static void callback();
protected:
private:
	const static int input_map[];
	static uint16_t controller_vals[];
	static int current_controller;
	
	static void init_adc(uint8_t analog_controller_map);
	static void init_digital(uint8_t digital_controller_map);
	static void read();
	static void setup_read();

}; //Controller

#endif //__CONTROLLER_H__
