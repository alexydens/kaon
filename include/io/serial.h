/* Include guard */
#ifndef _IO_SERIAL_H
#define _IO_SERIAL_H

/* Serial ports */

/* Includes */
#include <utils.h>
#include <io/port.h>

/* Consts */
/* The serial ports themselves */
/* The base port of serial0 */
#define SERIAL0_BASE_PORT           0x3F8
/* The base port of serial1 */
#define SERIAL1_BASE_PORT           0x2F8
/* The base port of serial2 */
#define SERIAL2_BASE_PORT           0x3E8
/* The base port of serial3 */
#define SERIAL3_BASE_PORT           0x2E8
/* The base port of serial4 */
#define SERIAL4_BASE_PORT           0x5F8
/* The base port of serial5 */
#define SERIAL5_BASE_PORT           0x4F8
/* The base port of serial6 */
#define SERIAL6_BASE_PORT           0x5E8
/* The base port of serial7 */
#define SERIAL7_BASE_PORT           0x4E8
/* The offsets from the base ports */
/* The data port */
#define SERIAL_DATA(port)           (port)
/* The first in first out command port */
#define SERIAL_FIFO_COMMAND(port)   (port + 2)
/* The line command port */
#define SERIAL_LINE_COMMAND(port)   (port + 3)
/* The modem command port */
#define SERIAL_MODEM_COMMAND(port)  (port + 4)
/* The status port */
#define SERIAL_LINE_STATUS(port)    (port + 5)
/* The commands */
/* Set the dlab (divisor latch access bit) */
#define SERIAL_LINE_DLAB            0x80

/* Initialize the serial port */
extern void serial_init(void);
/* Send buffer to serial port */
extern void serial_send(u8 *buf, u16 len);
/* Send null terminated string to serial port */
extern void serial_puts(char *str);
/* Check if transmit buffer is empty */
extern bool serial_tx_empty(void);

#endif /* _IO_SERIAL_H */
