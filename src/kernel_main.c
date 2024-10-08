/* Includes */
#include <utils.h>
#include <io/vga_text_term.h>
#include <io/serial.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <sys/paging.h>
#include <external/multiboot.h>

/* Logging */
#define LOG(str) do{vga_text_puts(str);serial_puts(str);}while(0)

/* Keyboard handler */
void keyboard_handler(irq_args_t *args) {
  /* Print message */
  LOG("Scancode: 0x");
  /* Get scancode */
  u8 scancode = port_in_8(0x60);
  /* Print scancode */
  char str[3];
  hex_str_8(scancode, str);
  str[2] = 0;
  LOG(str);
  /* Print newline and if down/up */
  if (scancode & 0x80)
    LOG(" (up)\r\n");
  else
    LOG(" (down)\r\n");
  (void)args;
}

/* Kernel entry point */
void kernel_main(multiboot_info_t *mb_info) {
  /* Initialize vga text terminal */
  /*vga_text_set_color(VGA_TEXT_COLOR_GREEN, VGA_TEXT_COLOR_BLACK);*/
  vga_text_set_color(VGA_TEXT_COLOR_LIGHT_GREY, VGA_TEXT_COLOR_BLUE);
  vga_text_set_cursor(0, 0);
  vga_text_clear(0);
  LOG("===> Initialized VGA Text Mode Terminal.\r\n");
  /* Initialize GDT */
  gdt_init();
  LOG("===> Initialized Global Descriptor Table.\r\n");
  /* Initialize GDT */
  idt_init();
  add_irq_handler(1, keyboard_handler);
  LOG("===> Initialized Interrupt Descritpor Table.\r\n");
  /* Initialize paging */
  paging_init();
  LOG("===> Initialized paging.\r\n");
  /* Initialize serial port */
  serial_init();
  LOG("===> Initialized serial port.\r\n");

  /* Test multiboot info */
  /* Convert mb_info to virtual address space */
  mb_info = (multiboot_info_t *)((u32)mb_info + 0xC0000000);
  LOG("===> Multiboot info:\r\n");
  LOG("ADDR OF INFO: 0x");
  char str[9]; /* Space for hex strings */
  str[8] = 0;
  hex_str_32((u32)mb_info, str);
  LOG(str);
  LOG("\r\n");
  LOG("FLAGS: 0x");
  hex_str_32(mb_info->flags, str);
  LOG(str);
  LOG("\r\n");
  for (int i = 0; i < mb_info->mmap_length; i+= sizeof(multiboot_memory_map_t)) {
    multiboot_memory_map_t *mb_map =
      (multiboot_memory_map_t *)(mb_info->mmap_addr + i + 0xC0000000);
    LOG("\tFrom: 0x");
    hex_str_32(mb_map->addr, str);
    LOG(str);
    LOG(" Length: 0x");
    hex_str_32(mb_map->addr + mb_map->len, str);
    LOG(str);
    LOG(" Size: 0x");
    hex_str_32(mb_map->addr + mb_map->size, str);
    LOG(str);
    LOG(" Type: 0x");
    hex_str_32(mb_map->type, str);
    LOG(str);
    LOG("\r\n");
  }
  LOG("MEM UPPER: 0x");
  hex_str_32(mb_info->mem_upper, str);
  LOG(str);
  LOG("\r\n");
  LOG("MEM LOWER: 0x");
  hex_str_32(mb_info->mem_lower, str);
  LOG(str);
  LOG("\r\n");

  /* Test */
  *((u8 *)0xc0400000) = 0xea;
  __asm__ __volatile__ ("int $0x3");
  serial_puts("Hello, World!\r\n");

  /* Haltt */
  while (1);
  __asm__ __volatile__ ("cli; hlt");
}
