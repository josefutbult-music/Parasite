#ifndef __OUTPUT_HANDLER_H__
#define __OUTPUT_HANDLER_H__

#include <stdint.h>

class Output_Handler
{
public:
	static void init();
	static int write(uint8_t channel, uint8_t val);

protected:
private:

	// static const uint8_t analog_output_map[6] = {3, 2, 5, 4, 1, 0};

};

#endif //__OUTPUT_HANDLER_H__
