/* Include guard */
#ifndef _CONF_H
#define _CONF_H

/* Some stuff that I have had to choose, to avoid magic values later on. */

/* Includes */
#include "types.h"

/* Physical start address of kernel */
#define _PHYS_START_KERNEL          (&_phys_start_kernel)
extern u32 _phys_start_kernel;
/* Physical end address of kernel */
#define _PHYS_END_KERNEL            (&_phys_end_kernel)
extern u32 _phys_end_kernel;
/* Virtual start address of kernel */
#define _START_KERNEL               (&_start_kernel)
extern u32 _start_kernel;
/* Virtual end address of kernel */
#define _END_KERNEL                 (&_end_kernel)
extern u32 _end_kernel;

/* Address of initial page directory */
#define _INIT_PD                    (&_init_PD)
extern u32 _init_PD;
/* Address of initial page table */
#define _INIT_PT0                   (&_init_PT0)
extern u32 _init_PT0;

/* Generic GDT segment selector */
#define GDT_SEGMENT_SELECTOR(segment, dpl) ((segment) << 3 | (dpl))

/* Selectors for segments */
#define GDT_SEGMENT_CODE     GDT_SEGMENT_SELECTOR(1, 0)
#define GDT_SEGMENT_DATA     GDT_SEGMENT_SELECTOR(2, 0)
#define GDT_SEGMENT_USERCODE GDT_SEGMENT_SELECTOR(3, 3)
#define GDT_SEGMENT_USERDATA GDT_SEGMENT_SELECTOR(4, 3)

#endif /* _CONF_H */
