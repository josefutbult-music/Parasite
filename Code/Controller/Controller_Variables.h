#ifndef CONTROLLER_VARIABLES_H_
#define CONTROLLER_VARIABLES_H_

#define CONTROLLER_LENGTH 3
#define ANALOG_THRESHOLD 10
#define MAX_OUTPUTS 1

#define ANALOG_TYPE_LINEAR 0
#define ANALOG_TYPE_LOGARITHMIC 1

#define ANALOG_CONTROLLER 0
#define DIGITAL_CONTROLLER 1

#define ANALOG_OUTPUT 0
#define DIGITAL_OUTPUT 1

struct Output {
	// Type of output (ANALOG_OUTPUT, DIGITAL_OUTPUT)
	int type;
	// Address of the output IC
	int addres;
	// Pin on the output IC
	int pin;
	// The max value that the controller value should map to
	int max_threashold;
	// The min value that the controller value should map to
	int min_threashold;
	// The translate function for an analog output (ANALOG_TYPE_LINEAR, ANALOG_TYPE_LOGARITHMIC)
	int analog_type;
};

struct Controller_map {
	int type;
	struct Output output[MAX_OUTPUTS];
};

#endif /* CONTROLLER_VARIABLES_H_ */