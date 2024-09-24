/* Implements sys/gdt.h */
#include <sys/gdt.h>

/* Globals */
/* The global descriptor table */
static gdt_entry_t _gdt[5];
/* The GDT descriptor */
static gdtr_t _gdtr;

/* Initialize the gdt */
void gdt_init(void) {
  /* Null entry */
  _gdt[0] = gdt_entry(0, 0, 0, 0);
  /* Code segment - kernel */
  _gdt[1] = gdt_entry(
      0, 0xffffffff,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_DPL0
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_EXEC
      | GDT_ACCESS_CONFORMS
      | GDT_ACCESS_READABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );
  /* Data segment - kernel */
  _gdt[2] = gdt_entry(
      0, 0xffffffff,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_DPL0
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_WRITABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );
  /* Code segment - user */
  _gdt[3] = gdt_entry(
      0, 0xffffffff,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_DPL3
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_EXEC
      | GDT_ACCESS_CONFORMS
      | GDT_ACCESS_READABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );
  /* Data segment - user */
  _gdt[4] = gdt_entry(
      0, 0xffffffff,
      GDT_ACCESS_PRESENT
      | GDT_ACCESS_DPL3
      | GDT_ACCESS_NOTSYS
      | GDT_ACCESS_WRITABLE
      | GDT_ACCESS_ACCESSED,
      GDT_FLAGS_GRANULARITY
      | GDT_FLAGS_32BIT
  );
  /* Load the global descriptor table */
  _gdtr.base = (u32)(&_gdt);
  _gdtr.limit = sizeof(gdt_entry_t) * 5 - 1;

  /* Load GDT */
  __asm__ __volatile__ ("lgdt %0" : : "m" (_gdtr));

  /* Enable protected mode */
  __asm__ __volatile__ ("mov %cr0, %eax");
  __asm__ __volatile__ ("or $0x1, %eax");
  __asm__ __volatile__ ("mov %eax, %cr0");

  /* Load the segment registers */
  __asm__ __volatile__ ("mov $0x10, %ax");
  __asm__ __volatile__ ("mov %ax, %ds");
  __asm__ __volatile__ ("mov %ax, %es");
  __asm__ __volatile__ ("mov %ax, %fs");
  __asm__ __volatile__ ("mov %ax, %gs");
  __asm__ __volatile__ ("mov %ax, %ss");

  /* Jump to 32-bit protected mode */
  __asm__ __volatile__ ("ljmp $0x08, $1f");
  __asm__ __volatile__ ("1:");
}
