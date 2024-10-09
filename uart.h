#ifndef __UART_H__
#define __UART_H__
#include <stdint.h>

char uart_getc(void);
void uart_putc(const char c);
void uart_puthex(uint64_t n);
void uart_putdec(uint64_t n);
void uart_puts(const char *s);
void log(const char *s1, const char *s2, const char *s3);

#endif /* __UART_H__ */