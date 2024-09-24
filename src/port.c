/* Implements io/port.h */
#include <io/port.h>

/* Read in a byte from a port */
u8 port_in_8(u16 port) {
  u8 val;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (val) : "Nd" (port));
  return val;
}
/* Read in a word from a port */
u16 port_in_16(u16 port) {
  u16 val;
  __asm__ __volatile__ ("inw %1, %0" : "=a" (val) : "Nd" (port));
  return val;
}
/* Write a byte to a port */
void port_out_8(u16 port, u8 data) {
  __asm__ __volatile__ ("outb %0, %1" : : "a" (data), "Nd" (port));
}
/* Write a word to a port */
void port_out_16(u16 port, u16 data) {
  __asm__ __volatile__ ("outw %0, %1" : : "a" (data), "Nd" (port));
}
