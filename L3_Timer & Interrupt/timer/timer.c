#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "peripherals/gpio.h"
const unsigned int interval = 200000;
unsigned int curVal = 0;
int count = 0;
void timer_init ( void )
{
	curVal = get32(TIMER_CLO);
	curVal += interval;
	put32(TIMER_C1, curVal);
}
void handle_timer_irq( void ) 
{
	curVal += interval;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1); // inform cpu timer1 interrupt occurs
	printf("Timer 1 interrupt received\n\r");
	count = count%2;
	if(!count)
		put32(GPSET0,1<<5);
	else
		put32(GPCLR0,1<<5);
	count++;
	
}

