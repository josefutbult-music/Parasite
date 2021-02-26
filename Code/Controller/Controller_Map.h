#ifndef CONTROLLER_MAP_H_
#define CONTROLLER_MAP_H_

#include "Controller_Variables.h"

static const struct Controller_map controller_map[CONTROLLER_LENGTH] = {
	{ 
		// Controller type
		DIGITAL_CONTROLLER, 
		{
			// Output type
			DIGITAL_OUTPUT,
			// Addres to IC
			0,
			// Pin on IC
			0
		}
	},
	{
		// Controller type
		ANALOG_CONTROLLER,
		{
			// Output type
			ANALOG_OUTPUT,
			// Addres to IC
			0,
			// Pin on IC 
			0, 
			// Max threshold
			255, 
			// Min threshold
			0,
			// Analog translation function
			ANALOG_TYPE_LINEAR
		}
	},
	{
		// Controller type
		ANALOG_CONTROLLER,
		{
			// Output type
			ANALOG_OUTPUT,
			// Addres to IC
			0,
			// Pin on IC 
			1,
			// Max threshold
			255,
			// Min threshold
			0,
			// Analog translation function
			ANALOG_TYPE_LINEAR
		}
	}
};

#endif /* CONTROLLER_MAP_H_ */