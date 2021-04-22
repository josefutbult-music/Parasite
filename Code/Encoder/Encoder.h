/* 
* Encoder.h
*
* Created: 2021-04-22 14:52:13
* Author: josef
*/


#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <stdint.h>

class Encoder
{
public:
	static void init();
	static int get_increment_val();
	static int get_buttonpress();
	static void on_interrupt();
protected:
private:
	static uint8_t input_state;
	static int increment_val;
	static int buttonpress;

};

#endif //__ENCODER_H__
