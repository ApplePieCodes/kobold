#include <stdint.h>
#include <bits.h>

#define PML1_SHIFT 12
#define PML2_SHIFT 21
#define PML3_SHIFT 30
#define PML4_SHIFT 39

#define PAGE_INDEX(virt, shift) (virt >> shift) & 0x1FF

#define PRESENT_BIT BIT(0)
#define WRITABLE_BIT BIT(1)
#define USER_BIT BIT(2)
#define WRITETHROUGH_BIT BIT(3)
#define CACHE_DISABLE_BIT BIT(4)
#define ACCESSED_BIT BIT(5)
#define DIRTY_BIT BIT(6)
#define SIZE_BIT BIT(7)
#define GLOBAL_BIT BIT(8)
#define NOEXECUTE_BIT BIT(63)

// RIGHT SHIFT THIS
#define ADDRESS_OFFSET 12
#define PAGE_MASK 0x000FFFFFFFFFF000
#define PAGE_ADDRESS(page) ((page & PAGE_MASK) >> ADDRESS_OFFSET)

typedef uint64_t page_table_t[512];

extern page_table_t kernel_pagemap;

void vmmMapPage(uint64_t *pagemap, uint64_t virtualAddress, uint64_t physicalAddress, uint8_t flags);
void vmmLoadPagemap(uint64_t *map);
void initVMM();