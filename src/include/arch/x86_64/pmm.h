#ifndef PMM_H
#define PMM_H

#include <stdint.h>
#define PAGE_SIZE 4096

void initPMM();

void* pmmAalloc(uint64_t size);
void* pmmAllocz(uint64_t size);
void* pmmRealloc(void * ptr, uint64_t old_size, uint64_t new_size);
void pmmFree(void * ptr, uint64_t size);

#endif