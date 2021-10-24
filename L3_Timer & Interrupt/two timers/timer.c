#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "peripherals/gpio.h"
// const unsigned int interval = 200000;
const unsigned int interval = 200000;
const unsigned int interval3 = 2000000;
unsigned int curVal = 0;
unsigned int curVal_3 = 0;
unsigned led_state = 0;
// unsigned int set = 286331153;
// unsigned int clr = 4008636142;
// unsigned int set = b'00010001000100010001000100010001';
// unsigned int clr = b'11101110111011101110111011101110';
int set[4]={1,2,4,8};
int clr[4]={15,13,11,7};
int count = 0;
void timer_init ( void )
{
	curVal = get32(TIMER_CLO);
	curVal += interval;
	put32(TIMER_C1, curVal);
}

void timer_init_3 ( void )
{
	curVal_3 = get32(TIMER_CLO);
	curVal_3 += interval3;
	put32(TIMER_C3, curVal_3);
}



void handle_timer_irq( void ) 
{
	curVal += interval;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1); // inform cpu timer1 interrupt occurs

	printf("Timer 1 interrupt received\n\r");
	count = count % 4;
	put32(GPCLR0,clr[count]<<5);
	put32(GPSET0,set[count++]<<5);
	
}



void handle_timer_irq_3( void ) 
{
	curVal_3 += interval3;
	put32(TIMER_C3, curVal_3);
	put32(TIMER_CS, TIMER_CS_M3);

	printf("Timer 3 interrupt received\n\r");
	if(led_state){
		put32(GPCLR0,15<<5);
		led_state = 0;
	}
	else{
		put32(GPSET0,15<<5);
		led_state = 1;
	}

}


