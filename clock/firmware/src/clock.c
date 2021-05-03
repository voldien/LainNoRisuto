/**
 *	The following code is for the DS1307 clock IC.
 */
#include"clock.h"
#include"core/i2c.h"
#include<avr/pgmspace.h>

/*	Device register addresses.	*/
static const uint8_t devaddr = 0b11010000;
static const uint8_t reg_seconds = 0x00;
static const uint8_t reg_minutes = 0x01;
static const uint8_t reg_hours = 0x02;
static const uint8_t reg_days = 0x03;
static const uint8_t reg_date = 0x04;
static const uint8_t reg_month = 0x05;
static const uint8_t reg_year = 0x06;
static const uint8_t reg_control = 0x07;


static void disableOscillator(){
	const uint8_t enable = 0;///(0 << 7);
	i2c_transmitreg(devaddr, reg_control, &enable, 1);
}
static void enableOscillator(){
	const uint8_t enable = (1 << 7);
	i2c_transmitreg(devaddr, reg_control, &enable, 1);
}

static inline void convertDay2Dec(CurrentDayTime* time){
	time->sec = ((time->sec & 0x70) >> 3) * 10 + (time->sec & 0xF);
	time->hour = time->hour & 0x40 ? time->hour & 0x1F : time->hour & 0x3;
}

static inline void convertDate2Dec(CurrentDateTime* date){

}

static void setDefaultTime(void){
	const uint8_t deftime[] = {
			0,				/*	Seconds.	*/
			51,				/*	Minutes.	*/
			0x08+0x40,		/*	Hours.	*/
			0x01,			/*	Week Day.	*/
			0x01,			/*	Day.	*/
			0x16,			/*	Month.	*/
			5				/*	Year from */
	};

	i2c_transmitreg(devaddr, reg_seconds, deftime, sizeof(deftime));
}

void setClockEnable(void) {
	disableOscillator();
	setDefaultTime();
	enableOscillator();
}

void getClockCurrentDayTime(CurrentDayTime* time) {
	if(i2c_receivereg(devaddr, reg_seconds, &time->sec, 3) == 0)
		convertDay2Dec(time);
}

void getClockCurrentDate(CurrentDateTime* pdate) {

	union{
		uint8_t days, date, month, year;
		uint8_t udate[4];
	}update;

	/*	Fetch date.	*/
	i2c_receivereg(devaddr, reg_days, update.udate, sizeof(update.udate));
}

void setClockControl(ClockControlSettings* control) {
	i2c_transmitreg(devaddr, reg_control, &control->control, 1);
}
