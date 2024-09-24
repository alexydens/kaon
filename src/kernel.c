/* Includes */
#include <utils.h>
#include <io/vga_text_term.h>

/* Kernel entry point */
void kernel_main(void) {
  /* Initialize vga text terminal */
  /*vga_text_set_color(VGA_TEXT_COLOR_GREEN, VGA_TEXT_COLOR_BLACK);*/
  vga_text_set_color(VGA_TEXT_COLOR_LIGHT_GREY, VGA_TEXT_COLOR_BLUE);
  vga_text_set_cursor(0, 0);
  vga_text_clear(0);
  vga_text_puts("===> Initialized Global Descriptor Table.\r\n");
  vga_text_puts("===> Initialized VGA Text Mode Terminal.\r\n");

  /* Halt */
  __asm__ __volatile__ ("cli; hlt");
}
