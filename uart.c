#include "uart.h"

volatile unsigned int *const UART0DR = (unsigned int *)0x09000000;
volatile unsigned int *const UART0FR = (unsigned int *)0x09000018;

/* -------------------------------------------------------------------------------
 *  From AMBA UART (PL010) Block Specification
 * -------------------------------------------------------------------------------
 *  UART Register Offsets.
 */
#define UART01x_DR		0x00	/* Data read or written from the interface. */
#define UART01x_RSR		0x04	/* Receive status register (Read). */
#define UART01x_ECR		0x04	/* Error clear register (Write). */
#define UART010_LCRH		0x08	/* Line control register, high byte. */
#define ST_UART011_DMAWM	0x08    /* DMA watermark configure register. */
#define UART010_LCRM		0x0C	/* Line control register, middle byte. */
#define ST_UART011_TIMEOUT	0x0C    /* Timeout period register. */
#define UART010_LCRL		0x10	/* Line control register, low byte. */
#define UART010_CR		0x14	/* Control register. */
#define UART01x_FR		0x18	/* Flag register (Read only). */
#define UART010_IIR		0x1C	/* Interrupt identification register (Read). */
#define UART010_ICR		0x1C	/* Interrupt clear register (Write). */
#define ST_UART011_LCRH_RX	0x1C    /* Rx line control register. */
#define UART01x_ILPR		0x20	/* IrDA low power counter register. */
#define UART011_IBRD		0x24	/* Integer baud rate divisor register. */
#define UART011_FBRD		0x28	/* Fractional baud rate divisor register. */
#define UART011_LCRH		0x2c	/* Line control register. */
#define ST_UART011_LCRH_TX	0x2c    /* Tx Line control register. */
#define UART011_CR		0x30	/* Control register. */
#define UART011_IFLS		0x34	/* Interrupt fifo level select. */
#define UART011_IMSC		0x38	/* Interrupt mask. */
#define UART011_RIS		0x3c	/* Raw interrupt status. */
#define UART011_MIS		0x40	/* Masked interrupt status. */
#define UART011_ICR		0x44	/* Interrupt clear register. */
#define UART011_DMACR		0x48	/* DMA control register. */
#define ST_UART011_XFCR		0x50	/* XON/XOFF control register. */
#define ST_UART011_XON1		0x54	/* XON1 register. */
#define ST_UART011_XON2		0x58	/* XON2 register. */
#define ST_UART011_XOFF1	0x5C	/* XON1 register. */
#define ST_UART011_XOFF2	0x60	/* XON2 register. */
#define ST_UART011_ITCR		0x80	/* Integration test control register. */
#define ST_UART011_ITIP		0x84	/* Integration test input register. */
#define ST_UART011_ABCR		0x100	/* Autobaud control register. */
#define ST_UART011_ABIMSC   0x15C /* Autobaud interrupt mask/clear register. */

#define LCRH_FEN (1 << 4)
#define LCRH_WLEN_8BIT (3 << 5)

#define UART011_FR_RI         0x100
#define UART011_FR_TXFE       0x080
#define UART011_FR_RXFF       0x040
#define UART01x_FR_TXFF       0x020
#define UART01x_FR_RXFE       0x010
#define UART01x_FR_BUSY       0x008
#define UART01x_FR_DCD        0x004
#define UART01x_FR_DSR        0x002
#define UART01x_FR_CTS        0x001
#define UART01x_FR_TMSK       (UART01x_FR_TXFF + UART01x_FR_BUSY)

static inline void cpu_relax(void)
{
	asm volatile("yield" ::: "memory");
}

void uart_putc(const char c)
{
	// Wait for UART to become ready to transmit.
	while ((*UART0FR) & (1 << 5)) {
		cpu_relax();
	}
	*UART0DR = c; /* Transmit char */
	while (*UART0DR & UART01x_FR_BUSY) {
		cpu_relax();
	}
}

char uart_getc(void)
{
	while ((*UART0FR) & UART01x_FR_RXFE)
		;
	return *(UART0DR);
}

void uart_puthex(uint64_t n)
{
	const char *hexdigits = "0123456789ABCDEF";

	uart_putc('0');
	uart_putc('x');
	for (int i = 60; i >= 0; i -= 4) {
		uart_putc(hexdigits[(n >> i) & 0xf]);
		if (i == 32)
			uart_putc(' ');
        }
	uart_putc('\n');
}
void uart_putdec(uint64_t number)
{
	// 处理负数（可选）
	if (number < 0) {
		uart_putc('-');
		number = -number;
	}

	// 将数字转换为字符并发送
	if (number == 0) {
		uart_putc('0');
		return;
	}

	char buffer[10];
	int i = 0;

	// 将数字转换为字符
	while (number > 0) {
		buffer[i++] = (number % 10) + '0'; // 取余并转换为字符
		number /= 10;
	}

	// 反转字符数组并发送
	while (--i >= 0) {
		uart_putc(buffer[i]);
	}
	uart_putc('\n');
}

void uart_puts(const char *s)
{
	while (*s != '\0') { /* Loop until end of string */
		*UART0DR = (unsigned int)(*s); /* Transmit char */
		s++; /* Next char */
        }

}

void puts(const char *str)
{
	while (*str) {
		uart_putc(*str++);
	}
}

void putchar(char c) { uart_putc(c); }

void log(const char *s1, const char *s2, const char *s3) {
  uart_puts(s1);
  uart_puts(s2);
  uart_puts(s3);
}