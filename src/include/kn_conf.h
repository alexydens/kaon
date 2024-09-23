/* Include guard */
#ifndef _KN_CONF_H
#define _KN_CONF_H

/* Some stuff that I have had to choose, to avoid magic values later on. */

/* Includes */
#include "kn_types.h"

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

#endif /* _KN_CONF_H */
