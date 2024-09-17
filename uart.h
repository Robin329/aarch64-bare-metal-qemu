#include <stdint.h>

char uart_getc(void);
void uart_putc(const char c);
void uart_puthex(uint64_t n);
void uart_puts(const char *s);