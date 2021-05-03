/**
 *	The following code is for the LM75 temperature IC.
 */
#include"temperature.h"
#include"core/i2c.h"
#include<avr/io.h>

/*	Adjustable slave address bits.	*/
#define A0 0
#define A1 0
#define A2 0

/*	Slave address and registers address.	*/
static const uint8_t devaddr = (0b10010000 | (A0 << 2) | (A1 << 1) | (A2 << 0));
static const uint8_t reg_temp_read = 0b000;
static const uint8_t reg_temp_conf = 0b001;
static const uint8_t reg_productid = 0b111;

void getCurrentTemperaturePart(int8_t* __restrict__ major, uint8_t* __restrict__ minor){
	uint16_t temperature;
	getCurrentTemperature(&temperature);

	/*	Decode temperature values.	*/
	*major = (temperature >> 0) & 0xff;
	*minor = (temperature >> 8) ? 5 : 0;
}

void getCurrentTemperature(uint16_t* temperature){
	i2c_receivereg(devaddr, reg_temp_read, (uint8_t*)temperature, 2);
}

void readCurrentConfig(uint8_t* config){
	i2c_receivereg(devaddr, reg_temp_conf, config, 1);
}

void writeCurrentConfig(const uint8_t* config){
	i2c_transmitreg(devaddr, reg_temp_conf, config, 1);
}

uint8_t checkTemperaturePresent(void){
	uint8_t product = 0;
	const uint8_t ret = i2c_receivereg(devaddr, reg_productid, &product, sizeof(product));
	if(ret != 0)
		return 0;
	return !(ret && ((product & 0b11100000) == 0b10100000));
}
