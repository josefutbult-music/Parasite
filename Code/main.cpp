#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>
#include<avr/interrupt.h>

#include "Display/Display.h"
#include "Encoder/Encoder.h"
#include "Controller/Controller.h"
#include "Controller/Controller_Variables.h"
#include "Output/Output_Handler.h"

uint16_t output_map(Output output, double value)
{
	return	(uint8_t)	(((double)output.max_threashold - (double)output.min_threashold) * value +
						(double)output.min_threashold);
}

void handle_controllchange(int channel)
{
	Controller_map current_controller = controller_map[channel];
	
	if(current_controller.type == DIGITAL_CONTROLLER){
		Display::set_disp_val(Controller::get_controller_val(channel));
		
		for (int i = 0; i < MAX_OUTPUTS; i++ )
		{
			Output output = current_controller.output[i];
			
			switch (output.type)
			{
				case ANALOG_OUTPUT:
					Output_Handler::write(output.channel, 
										Controller::get_controller_val(channel) ? 
										output.max_threashold :
										output.min_threashold
										);
					break;
					
				case DIGITAL_OUTPUT:
					// TODO: Add digtal output
					break;
				
				default:
					break;
			}
		}
	}
	else if(current_controller.type == ANALOG_CONTROLLER){
		Display::set_disp_val((double)Controller::get_controller_val(channel) / 10.24);
		
		for (int i = 0; i < MAX_OUTPUTS; i++ )
		{
			Output output = current_controller.output[i];
			
			switch (output.type)
			{
				case ANALOG_OUTPUT:
				Output_Handler::write(output.channel, 
					output_map(output, Controller::get_controller_val(channel) / 4));
				break;Q
				
				case DIGITAL_OUTPUT:
				// TODO: Add digtal output
				break;
				
				default:
				break;
			}
		}
	}
	
	
}

void read_controllers()
{
	if(Controller::get_controller_vals_changed())
	{
		for(int i = 0; i < CONTROLLER_LENGTH; i++){
			if((Controller::get_controller_vals_changed() >> i) & 1){
				handle_controllchange(i);
			}
		}
		Controller::clear_controller_vals_changed();
	}
}

int main(void)
{
    _delay_ms(100);
	Encoder::init();
	Display::init();
	Controller::init();
	Output_Handler::init();
		
    while(1){
		read_controllers();
	}
}

/*
for(int i = 0; i < CONTROLLER_LENGTH; i++ ){
	{
		int index = 0;
		for(int i = 0; i < CONTROLLER_LENGTH; i++){
			if((Controller::get_controller_vals_changed() >> i) & 1){
				index = i;
				break;
			}
		}
		
		
		
	}
}

}
*/