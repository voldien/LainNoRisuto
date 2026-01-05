#ifndef _CHRISTMAS_CARD_DEF_H_
#define _CHRISTMAS_CARD_DEF_H_ 1

/**
 * Push Button Registers and Pin.
 * Reset Button
 */
#define PUSH_BUTTON0_REG PORTB
#define PUSH_BUTTON0_DREG DDRB
#define PUSH_BUTTON0_IREG PINB
#define PUSH_BUTTON0_PIN PB0

/**
 * Push Button Registers and Pin
 * Next Button
 */
#define PUSH_BUTTON1_REG PORTA
#define PUSH_BUTTON1_DREG DDRA
#define PUSH_BUTTON1_IREG PINA
#define PUSH_BUTTON1_PIN PA1

/**
 * Shift Registers Output Enabled (SNx4HC595)
 * Pin and Registers.
 */
#define SHIFT_OE_REG PORTA /*		*/
#define SHIFT_OE_DREG DDRA /*		*/
#define SHIFT_OE_PIN PA0   /*		*/
#define SHIFT_OE_PWM_REG OCR0A

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

/**
 *
 */
#define WS2811_DREG DDRA
#define WS2811_REG PORTA
#define WS2811_PIN PA3

#define WS2811_IN (1 << WS2811_PIN)

#endif