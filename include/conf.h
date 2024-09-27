/* Include guard */
#ifndef _CONF_H
#define _CONF_H

/* Some stuff that I have had to choose, to avoid magic values later on. */

/* Includes */
#include <types.h>
#include <sys/gdt.h>

/* Physical start address of kernel */
#define PHYS_START_KERNEL           (&_phys_start_kernel)
extern u32 _phys_start_kernel;
/* Physical end address of kernel */
#define PHYS_END_KERNEL             (&_phys_end_kernel)
extern u32 _phys_end_kernel;
/* Virtual start address of kernel */
#define START_KERNEL                (&_start_kernel)
extern u32 _start_kernel;
/* Virtual end address of kernel */
#define END_KERNEL                  (&_end_kernel)
extern u32 _end_kernel;

/* Address of initial page directory */
#define INIT_PD                     (&_init_PD)
extern u32 _init_PD;
/* Address of initial page table */
#define INIT_PT0                    (&_init_PT0)
extern u32 _init_PT0;

/* Physical address of start of kernel code segment */
#define PHYS_START_KERNEL_CODE_SEG  (0x00000000)
/* Size of kernel code segment, in pages */
#define KERNEL_CODE_SEG_SIZE        (0xfffff)
/* Physical address of start of kernel data segment */
#define PHYS_START_KERNEL_DATA_SEG  (0x00000000)
/* Size of kernel data segment, in pages */
#define KERNEL_DATA_SEG_SIZE        (0xfffff)

/* Physical address of start of user code segment */
#define PHYS_START_USER_CODE_SEG    (0x00000000)
/* Size of user code segment, in pages */
#define USER_CODE_SEG_SIZE          (0xfffff)
/* Physical address of start of user data segment */
#define PHYS_START_USER_DATA_SEG    (0x00000000)
/* Size of user data segment, in pages */
#define USER_DATA_SEG_SIZE          (0xfffff)

/* Selector of kernel code segment */
#define SEG_SELECTOR_KERNELCODE     GDT_SEGMENT_SELECTOR(1, 0)
/* Selector of kernel data segment */
#define SEG_SELECTOR_KERNELDATA     GDT_SEGMENT_SELECTOR(2, 0)
/* Selector of user code segment */
#define SEG_SELECTOR_USERCODE       GDT_SEGMENT_SELECTOR(3, 3)
/* Selector of user data segment */
#define SEG_SELECTOR_USERDATA       GDT_SEGMENT_SELECTOR(4, 3)

/* The start of the memory reserved for the page tables */
#define PTE_MEM_START               (0xc0400000)
/* The size of the memory reserved for the page tables */
#define PTE_MEM_SIZE                (0x400000)


#endif /* _CONF_H */
