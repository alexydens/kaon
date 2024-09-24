/* Include guard */
#ifndef _SYS_GDT_H
#define _SYS_GDT_H

/* Managing the Global Descriptor Table */

/* Includes */
#include <types.h>

/* Consts */
/* Access byte */
#define GDT_ACCESS_PRESENT     (1 << 7)
#define GDT_ACCESS_DPL0        (0 << 5)
#define GDT_ACCESS_DPL1        (1 << 5)
#define GDT_ACCESS_DPL2        (2 << 5)
#define GDT_ACCESS_DPL3        (3 << 5)
#define GDT_ACCESS_NOTSYS      (1 << 4)
/* Non-system segment access byte: continued */
#define GDT_ACCESS_EXEC        (1 << 3)
#define GDT_ACCESS_CONFORMS    (1 << 2)
#define GDT_ACCESS_GROWDOWN    (1 << 2)
#define GDT_ACCESS_READABLE    (1 << 1)
#define GDT_ACCESS_WRITABLE    (1 << 1)
#define GDT_ACCESS_ACCESSED    (1 << 0)
/* System segment access byte: continued */
/* Postfixes: A = available, B = busy */
#define GDT_ACCESS_SYS_16TSSA  0x1
#define GDT_ACCESS_SYS_LDT     0x2
#define GDT_ACCESS_SYS_16TSSB  0x3
#define GDT_ACCESS_SYS_32TSSA  0x9
#define GDT_ACCESS_SYS_32TSSB  0xb
#define GDT_ACCESS_SYS_64TSSA  0x9
#define GDT_ACCESS_SYS_64TSSB  0xb
/* Flags */
#define GDT_FLAGS_GRANULARITY  (1 << 3)
#define GDT_FLAGS_32BIT        (1 << 2)
#define GDT_FLAGS_16BIT        (0 << 2)
#define GDT_FLAGS_64BIT        (1 << 1)

/* Macros */
#define GDT_SEGMENT_SELECTOR(segment, dpl) ((segment) << 3 | (dpl))

/* More consts - selectors for segments */
#define GDT_SEGMENT_CODE     GDT_SEGMENT_SELECTOR(1, 0)
#define GDT_SEGMENT_DATA     GDT_SEGMENT_SELECTOR(2, 0)
#define GDT_SEGMENT_USERCODE GDT_SEGMENT_SELECTOR(3, 3)
#define GDT_SEGMENT_USERDATA GDT_SEGMENT_SELECTOR(4, 3)

/* GDT Descriptor */
typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) gdtr_t;

/* GDT Entry */
typedef struct {
  u16  limit_low;
  u16  base_low;
  u8   base_middle;
  u8   access;
  u8   limit_middle: 4;
  u8   flags:        4;
  u8   base_high;
} __attribute__((packed)) gdt_entry_t;

/* Create a gdt entry */
static inline gdt_entry_t gdt_entry(
    u32 base,
    u32 limit,
    u8 access,
    u8 flags) {
  gdt_entry_t entry;
  entry.limit_low = limit & 0xffff;
  entry.base_low = base & 0xffff;
  entry.base_middle = (base >> 16) & 0xff;
  entry.access = access;
  entry.limit_middle = (limit >> 16) & 0x0f;
  entry.flags = flags;
  entry.base_high = (base >> 24) & 0xff;
  return entry;
}

/* Initialize the gdt */
extern void gdt_init(void);

#endif /* _SYS_GDT_H */
