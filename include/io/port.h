/* Include guard */
#ifndef _IO_PORT_H
#define _IO_PORT_H

/* Ported I/O interface */

/* Includes */
#include "types.h"

/* Read in a byte from a port */
extern u8 port_in_8(u16 port);
/* Read in a word from a port */
extern u16 port_in_16(u16 port);
/* Write a byte to a port */
extern void port_out_8(u16 port, u8 data);
/* Write a word to a port */
extern void port_out_16(u16 port, u16 data);

#endif /* _IO_PORT_H */
