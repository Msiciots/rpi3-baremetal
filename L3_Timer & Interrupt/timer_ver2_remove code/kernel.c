#include "printf.h"
#include "timer.h"
#include "irq.h"
#include "mini_uart.h"

void kernel_main(void)
{
	uart_init();
	init_printf(0, putc);
	irq_vector_init();

	

	
}
