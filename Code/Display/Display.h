#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

class Display
{
public:
	static uint16_t out_value;
	
	static void init();
	static void set_disp_val(uint8_t value);
	static void on_interrupt();
protected:
private:
	static uint8_t generate_digit(uint8_t value);
};

#endif