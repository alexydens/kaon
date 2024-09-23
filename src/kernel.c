/* Includes */
#include "include/kn_utils.h"

/* Kernel entry point */
void kernel_main(void) {
  *(u16 *)0xc03ff000 = 'A' | 15 << 8;
}
