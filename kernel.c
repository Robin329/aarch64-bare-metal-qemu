#include "uart.h"
#include "aarch64.h"
#include "board.h"
#include "gic_v3.h"
#include "timer.h"
#include "uart.h"
#include "printk.h"
#include <stdio.h>

void main()
{
	uart_puts("\n\n");
	uart_puts("************************************\n");
	uart_puts("*  Hello aarch64 baremetal QEMU!   *\n");
	uart_puts("************************************\n\n");
	uart_puts("timer test start .... \n\n");
	// GIC Init
	gic_v3_initialize();
	timer_test();
}
