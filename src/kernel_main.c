/* Includes */
#include <utils.h>
#include <io/vga_text_term.h>
#include <sys/gdt.h>
#include <sys/idt.h>

/* Keyboard handler */
void keyboard_handler(irq_args_t *args) {
  /* Print message */
  vga_text_puts("Scancode: 0x");
  /* Get scancode */
  u8 scancode = port_in_8(0x60);
  /* Print scancode */
  char str[3];
  hex_str_8(scancode, str);
  str[2] = 0;
  vga_text_puts(str);
  /* Print newline and if down/up */
  if (scancode & 0x80)
    vga_text_puts(" (up)\r\n");
  else
    vga_text_puts(" (down)\r\n");
  (void)args;
}

/* Kernel entry point */
void kernel_main(void) {
  /* Initialize vga text terminal */
  /*vga_text_set_color(VGA_TEXT_COLOR_GREEN, VGA_TEXT_COLOR_BLACK);*/
  vga_text_set_color(VGA_TEXT_COLOR_LIGHT_GREY, VGA_TEXT_COLOR_BLUE);
  vga_text_set_cursor(0, 0);
  vga_text_clear(0);
  vga_text_puts("===> Initialized VGA Text Mode Terminal.\r\n");
  /* Initialize GDT */
  gdt_init();
  vga_text_puts("===> Initialized Global Descriptor Table.\r\n");
  /* Initialize GDT */
  idt_init();
  add_irq_handler(1, keyboard_handler);
  vga_text_puts("===> Initialized Interrupt Descritpor Table.\r\n");

  /* Test */
  __asm__ __volatile__ ("int $0x3");

  /* Haltt */
  while (1);
  __asm__ __volatile__ ("cli; hlt");
}
