#include "printf.h"
#include "timer.h"
#include "irq.h"
#include "mini_uart.h"

void kernel_main(void)
{
	uart_init();
	init_printf(0, putc);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();

	while(1){
	enable_irq();
	uart_send(uart_recv());
	disable_irq();
	uart_recv();
	}
}
