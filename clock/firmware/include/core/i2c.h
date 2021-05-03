#ifndef _I2C_H_
#define _I2C_H_ 1
#include<avr/io.h>

/**
 *	Compute B
 */
#define i2c_compute_br(fcpu, fscl, presclar) ((((fcpu / fscl) / presclar) - 16 ) / 2)

/**
 *	Initialize I2C.
 */
extern void i2c_init(const uint8_t br);

/**
 *
 */
extern void i2c_eint(void);

/**
 *
 */
extern void i2c_dint(void);

extern uint8_t i2c_start(uint8_t addr);
extern uint8_t i2c_writechar(uint8_t c);
extern uint8_t i2c_read_ack(void);
extern uint8_t i2c_read_nack(void);
extern void i2c_stop(void);


extern uint8_t i2c_transmit(uint8_t dev, const uint8_t* data, uint8_t len);
extern uint8_t i2c_transmitreg(uint8_t dev, uint8_t reg, const uint8_t* data, uint8_t len);
extern uint8_t i2c_receive(uint8_t dev, uint8_t* data, uint8_t len);
extern uint8_t i2c_receivereg(uint8_t dev, uint8_t reg, uint8_t* data, uint8_t len);

/**
 *
 */
extern uint8_t i2c_detect(uint8_t dev);

#endif
