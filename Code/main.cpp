#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>

#include "Display/Display.h"
#include "Encoder/Encoder.h"
#include "Controller/Controller.h"
#include "Controller/Controller_Variables.h"
#include "Output/Output_Handler.h"

int main(void)
{
    _delay_ms(100);
	Display::init();
	Encoder::init();
	Controller::init();
	Output_Handler::init();
	
    while(1){
		for(int i = 0; i < CONTROLLER_LENGTH; i++ ){
			if(Controller::get_controller_vals_changed()){
				int index = 0;
				for(int i = 0; i < CONTROLLER_LENGTH; i++){
					if((Controller::get_controller_vals_changed() >> i) & 1){
						index = i;
						break;
					}
				}
				
				if(controller_map[index].type == DIGITAL_CONTROLLER){
					// Display::set_disp_val(Controller::get_controller_val(index));
				}
				else if(controller_map[index].type == ANALOG_CONTROLLER){
					// Display::set_disp_val((double)Controller::get_controller_val(index) / 10.24);
				}
				Controller::clear_controller_vals_changed();
			}
		}
    }
}

