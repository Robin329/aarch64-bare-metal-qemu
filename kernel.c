#include "uart.h"
#include "aarch64.h"
#include "board.h"
#include "gic_v3.h"
#include "timer.h"
#include "uart.h"
#include <stdint.h>

void main() {
  uart_puts("Hello world!\n");
  uart_puts("Hello aarch64 baremetal QEMU!\n");
  uart_puts("timer test start .... \n");
  uart_puts("Please input id>");
  uart_putc(uart_getc());
  uart_puts("\n");
  timer_test();
}
