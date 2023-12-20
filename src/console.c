#include "console.h"
#include "mini_uart.h"

#define MAX_BUFFER_SIZE  10
static char buffer[MAX_BUFFER_SIZE]; // Stores characters read from Mini UART to be returned by console_readline()

void console_init() {
	mini_uart_init();
}

void console_write(char* str) {
	char* c = str;
	while (*c) {
		mini_uart_tx(*c);
		c++;		
	}
}

char* console_readline() {
	char c;
	int i = 0;
	do {
		c = mini_uart_rx();
		buffer[i] = c;
		i++;
		if (i >= MAX_BUFFER_SIZE) {
			break;
		}
	} while (c != '\r');

	buffer[i - 1] = '\0';
	return buffer;
}
