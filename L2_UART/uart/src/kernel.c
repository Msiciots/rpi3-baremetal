#include "mini_uart.h"

void kernel_main(void)
{
	uart_init();
	// write code here
	uart_send_string("Hello world!\r\n");
}
