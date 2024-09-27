/* Implements io/serial.h */
#include <io/serial.h>

/* Consts */
#define DIVISOR 9600

/* Check if transmit buffer is empty */
bool serial_tx_empty(void) {
  return port_in_8(SERIAL_LINE_STATUS(SERIAL0_BASE_PORT)) & 0x20;
}

/* Send buffer to serial port */
void serial_send(u8 *buf, u16 len) {
  for (u16 i = 0; i < len; i++) {
    while (!serial_tx_empty());
    port_out_8(SERIAL_DATA(SERIAL0_BASE_PORT), buf[i]);
  }
}

/* Send null terminated string to serial port */
void serial_puts(char *str) {
  while (*str) {
    while (!serial_tx_empty());
    port_out_8(SERIAL_DATA(SERIAL0_BASE_PORT), *str);
    str++;
  }
}

/* Initialize the serial port */
void serial_init(void) {
  /* Configure baud rate */
  port_out_8(SERIAL_LINE_COMMAND(SERIAL0_BASE_PORT), SERIAL_LINE_DLAB);
  port_out_8(SERIAL_DATA(SERIAL0_BASE_PORT), (DIVISOR >> 8) & 0xFF);
  port_out_8(SERIAL_DATA(SERIAL0_BASE_PORT), DIVISOR & 0xFF);
  /* Configure the line */
  port_out_8(SERIAL_LINE_COMMAND(SERIAL0_BASE_PORT), 0x03);
  /* Configure the buffers */
  port_out_8(SERIAL_FIFO_COMMAND(SERIAL0_BASE_PORT), 0xC7);
  /* Configure the modem */
  port_out_8(SERIAL_MODEM_COMMAND(SERIAL0_BASE_PORT), 0x03);
}
