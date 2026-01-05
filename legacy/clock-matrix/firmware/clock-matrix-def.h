#ifndef _CLOCK_MATRIX_DEF_H_
#define _CLOCK_MATRIX_DEF_H_ 1


/**
 * Push Button Registers and Pin
 *
 */
#define PUSH_BUTTON_REG PORTB
#define PUSH_BUTTON_DREG DDRB
#define PUSH_BUTTON_IREG PINB
#define PUSH_BUTTON_PIN PB4

/**
 * Shift Registers Output Enabled (SNx4HC595)
 * Pin and Registers.
 */
#define SHIFT_OE_REG PORTB /*		*/
#define SHIFT_OE_DREG DDRB /*		*/
#define SHIFT_OE_PIN PB0   /*		*/
#define SHIFT_OE_PWM_REG OCR0B

/**
 * Shift Register Shift Clock Pin (SNx4HC595)
 * and Registers  (RCLK)
 */
#define SHIFT_RCLK_REG PORTB /*	 	*/
#define SHIFT_RCLK_DREG DDRB /*	 	*/
#define SHIFT_RCLK_PIN PB1	 /*	 	*/

/**
 * Shift Registers Serial Data Pin (SNx4HC595)
 * and Registers
 */
#define SHIFT_DIO_REG PORTB /*		*/
#define SHIFT_DIO_DREG DDRB /*		*/
#define SHIFT_DIO_PIN PB2	/*		*/

/**
 * Shift Registers Latch (Flush Data to Output) Pin (SNx4HC595)
 * and Register  (SRCLR)
 */
#define SHIFT_LATCH_REG PORTB
#define SHIFT_LATCH_DREG DDRB
#define SHIFT_LATCH_PIN PB3 /*	Shift clock.	*/

#endif