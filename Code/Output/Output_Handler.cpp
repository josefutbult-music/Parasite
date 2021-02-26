#include "Output_Handler.h"
#include "../Display/Display.h"
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>


void TWIInit()
{
	// Init I2C 1
	// Set bit rate prescaler
	TWSR1 = 0;
	// Set division factor (Both these two affect the SCK rate)
	TWBR1 = 0x0c;
	// Enable TWI (I2C)
	TWCR1 |= 1 << TWEN1;
}

void TWIStart()
{
	// Wait for TWI bus to clear
	while(TWCR1 & (1 << TWINT1));
	// Enable TWI, TWI interrupt and start signal
	TWCR1 = (1 << TWINT1) | (1 << TWSTA1) | (1 << TWEN1);
	// Wait for TWI bus to clear
	while(TWCR1 & (1 << TWINT1));
}

void TWIStop()
{
	// Wait for TWI bus to clear
	while(TWCR1 & (1 << TWINT1));
	// Enable TWI, TWI interrupt and stop signal
	TWCR1 = (1 << TWINT1) | (1 << TWSTO1) | (1 << TWEN1);
	// Wait for TWI bus to clear
	while(TWCR1 & (1 << TWINT1));
}

void TWIWrite(uint8_t data)
{
	// Wait for TWI bus to clear
	while(TWCR1 & (1 << TWINT1));
	// Write the data to the bus queue
	TWDR1 = data;
	// Enable TWI and TWI interrupt
	TWCR1 = (1 << TWINT1) | (1 << TWEN1);
	// Wait for TWI bus to clear
	while(TWCR1 & (1 << TWINT1));
}

uint8_t TWIReadAck()
{
	// Wait for TWI bus to clear
	while(TWCR1 & (1 << TWINT1));
	// Enable TWI, TWI interrupt and reading of ACK
	TWCR1 = (1 << TWEN1) | (1 << TWINT1) | (1 << TWEA1);
	// Wait for TWI bus to clear
	while(TWCR1 & (1 << TWINT1));
	// Return the result from I2C
	return TWDR1;
	
}

uint8_t TWIGetStatus()
{
	// Wait for TWI bus to clear
	while(TWCR1 & (1 << TWINT1));
	// Return upper 6 bit of TWI status register 
	return TWSR1 & 0xf8;
}

uint8_t i2c_write(uint8_t adress, uint8_t* data, int length)
{
	// Check pg 186 in the datasheet for TWI status codes
	TWIStart();
	// 0x08 - A Start condition has been transmitted
	uint8_t status = TWIGetStatus();
	if (status != 0x08)
		return status;
	// Write adress
	TWIWrite(adress << 1);
	// 0x18 - Slave address and write has been transmitted.	An ACK has been received.
	status = TWIGetStatus();
	if (status != 0x18)
		return status;
	// Write data
	for(int i = 0; i < length; i++){
		TWIWrite(data[i]);
		// 0x28 - Data byte has been transmitted, and ACK has been received
		status = TWIGetStatus();
		if (status != 0x28)
			return status;
	}
	TWIStop();
	
	return 0;
}

void Output_Handler::init()
{
	// 01011 - Chip address
	// 01 - Specified address
	uint8_t address = 0b0101101;
	
	// 1 - Channel 2
	// 0 - Midscale reset
	// 0 - Shutdown
	// 00 - Status of output pins
	// 000 - Dont care
	uint8_t data[2] = {0b10000000, 0xff};
	TWIInit();
	uint8_t status = i2c_write(address, data, 2);
	Display::set_disp_val(status / 10);
	_delay_ms(1000);
	Display::set_disp_val(status % 10);
	
}