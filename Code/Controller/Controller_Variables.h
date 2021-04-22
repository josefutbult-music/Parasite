#ifndef CONTROLLER_VARIABLES_H_
#define CONTROLLER_VARIABLES_H_

#define CONTROLLER_LENGTH 3
#define ANALOG_THRESHOLD 100
#define MAX_OUTPUTS 5

#define ANALOG_TYPE_LINEAR 0
#define ANALOG_TYPE_LOGARITHMIC 1

#define ANALOG_CONTROLLER 0
#define DIGITAL_CONTROLLER 1

#define NO_OUTPUT 0
#define ANALOG_OUTPUT 1
#define DIGITAL_OUTPUT 2

#define OUPTUT_NONE (Output *)0

struct Output {
	// Type of output (ANALOG_OUTPUT, DIGITAL_OUTPUT)
	int type;
	// Output channel (Analog: 0 - 5, Digital:  0 - 3)
	int channel;
	// The max value that the controller value should map to
	int max_threashold;
	// The min value that the controller value should map to
	int min_threashold;
	// The translate function for an analog output (ANALOG_TYPE_LINEAR, ANALOG_TYPE_LOGARITHMIC)
	int analog_type;
};

struct Controller_map {
	// Type of controller (ANALOG_CONTROLLER, DIGITAL_CONTROLLER)
	int type;
	// List of outputs controlled by controller
	struct Output output[MAX_OUTPUTS];
};

#endif /* CONTROLLER_VARIABLES_H_ */