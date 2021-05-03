#include"core/i2c.h"
#include<util/twi.h>

void i2c_init(const uint8_t br){
	TWBR = br;
}

void i2c_eint(void){
	TWCR |= (1 << TWINT) | (1 << TWIE);
}
void i2c_dint(void){
	TWCR &= ~(1 << TWINT  | (1 << TWIE));
}

uint8_t i2c_start(uint8_t addr){

	TWCR = 0;

	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/**/
	while(!(TWCR & (1 << TWINT)));

	/**/
	if( (TWSR & 0xF8) != TW_START){
		return 1;
	}

	TWDR = addr;

	TWCR = (1 << TWINT) | (1 << TWEN);

	/**/
	while( !(TWCR & (1 << TWINT)));

	uint8_t twst = (TW_STATUS & 0xF8);
	if( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK))
		return 1;

	return 0;
}

uint8_t i2c_writechar(uint8_t c){

	TWDR = c;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while( !(TWCR & (1 << TWINT)));

	if( (TWSR & 0xF8) !=  TW_MT_DATA_ACK){	return 1; }

	return 0;
}

uint8_t i2c_read_ack(void){

	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

	while( !(TWCR & ( 1 << TWINT)) );

	return TWDR;
}

uint8_t i2c_read_nack(void){

	TWCR = (1 << TWINT) | (1 << TWEN);

	while( !(TWCR & ( 1 << TWINT)) );

	return TWDR;

	return TWDR;
}

void i2c_stop(void){
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

uint8_t i2c_transmit(uint8_t dev, const uint8_t* data, uint8_t len){
	uint16_t x;
	i2c_start(dev | TW_WRITE);

	for(x = 0; x < len; x++){
		if( i2c_writechar(data[x]) ){
			return 1;
		}
	}


	i2c_stop();

	return 0;
}
uint8_t i2c_transmitreg(uint8_t dev, uint8_t reg, const uint8_t* data, uint8_t len){

	if (i2c_start(dev | TW_WRITE)){
		return 1;
	}

	i2c_writechar(reg);

	for (uint16_t i = 0; i < len; i++){
		if (i2c_writechar(data[i])){
			return 1;
		}
	}

	i2c_stop();

	return 0;
}

uint8_t i2c_receive(uint8_t dev, uint8_t* data, uint8_t len){

	uint16_t x;

	if(i2c_start(dev | TW_READ)){
		return 1;
	}

	for(x = 0; x < len - 1; x++){

		data[x] = i2c_read_ack();
	}

	data[len - 1] = i2c_read_nack();

	i2c_stop();

	return 0;
}

uint8_t i2c_receivereg(uint8_t devaddr, uint8_t reg, uint8_t* data, uint8_t len){

	uint16_t i;

	if (i2c_start(devaddr)){
		return 1;
	}

	i2c_writechar(reg);

	/*	Start reading once the REG has been transmitted.	*/
	if (i2c_start(devaddr | TW_READ)){
		return 1;
	}


	for (i = 0; i < (len - 1); i++){
		data[i] = i2c_read_ack();
	}
	data[(len-1)] = i2c_read_nack();

	i2c_stop();

	return 0;
}

uint8_t i2c_detect(uint8_t dev){

}
