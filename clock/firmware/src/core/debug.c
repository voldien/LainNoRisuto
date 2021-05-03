#include <stdarg.h>
#include <stdio.h>
#include "core/debug.h"

void uart_printf(const char* format, ...){
	uint8_t buf[128];
	va_list args;

	va_start (args, format);
	vsprintf (buf, format, args);
	va_end (args);

	uart_putstr(buf);
}
