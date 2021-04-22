#ifndef CONTROLLER_MAP_H_
#define CONTROLLER_MAP_H_

#include "Controller_Variables.h"

static const struct Controller_map controller_map[CONTROLLER_LENGTH] = {
	{ 
		// Controller type
		DIGITAL_CONTROLLER,
		{
			{
				// Output type
				DIGITAL_OUTPUT,
				// Max threshold
				1,
				// Min threshold
				0
			},
			{
				// Output type
				NO_OUTPUT
			},
			{
				// Output type
				NO_OUTPUT
			},
			{
				// Output type
				NO_OUTPUT
			},
			{
				// Output type
				NO_OUTPUT
			}
		}
	},
	{
		// Controller type
		ANALOG_CONTROLLER,
		{
			{
				// Output type
				ANALOG_OUTPUT,
				// Channel
				0,
				// Max threshold
				255, 
				// Min threshold
				0,
				// Analog translation function
				ANALOG_TYPE_LINEAR
			},
			{
				// Output type
				ANALOG_OUTPUT,
				// Channel
				1,
				// Max threshold
				0,
				// Min threshold
				255,
				// Analog translation function
				ANALOG_TYPE_LINEAR
			},
			{
				// Output type
				NO_OUTPUT
			},
			{
				// Output type
				NO_OUTPUT
			},
			{
				// Output type
				NO_OUTPUT
			}
		}
	},
	{
		// Controller type
		ANALOG_CONTROLLER,
		{
			{
				// Output type
				ANALOG_OUTPUT,
				// Channel
				2,
				// Max threshold
				255,
				// Min threshold
				0,
				// Analog translation function
				ANALOG_TYPE_LINEAR
			},
			{
				// Output type
				NO_OUTPUT
			},
			{
				// Output type
				NO_OUTPUT
			},
			{
				// Output type
				NO_OUTPUT
			},
			{
				// Output type
				NO_OUTPUT
			}
		}
	}
};

#endif /* CONTROLLER_MAP_H_ */