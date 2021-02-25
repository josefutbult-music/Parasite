#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>

#include "Display/Display.h"
#include "Encoder/Encoder.h"
#include "Controller/Controller.h"
#include "Controller/Controller_Map.h"

int main(void)
{
    _delay_ms(100);
	Display::init();
	Encoder::init();
	Controller::init();
	
	
	// Display::set_disp_val(3);
    while(1){
		for(int i = 0; i < CONTROLLER_LENGTH; i++ ){
			if(controller_map[i] == DIGITAL_CONTROLLER){
				Display::set_disp_val(Controller::get_controller_val(i));
			}
			else if(controller_map[i] == ANALOG_CONTROLLER){
				Display::set_disp_val((double)Controller::get_controller_val(i) / 10.24);
			}
			_delay_ms(1000);
		}
    }
}

