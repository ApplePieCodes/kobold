// The Kobold Kernel

// src/include/arch/x86_64/pmm.h

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

#ifndef PMM_H
#define PMM_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <term/term.h>
#include <spinlock.h>
#include <bootloader.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <colors.h>

#define PAGE_SIZE 4096

void initPMM();

extern uint8_t *bitmap;
extern uint64_t bitmap_size;

void* pmmAlloc(uint64_t size);
void* pmmAllocz(uint64_t size);
void* pmmRealloc(void * ptr, uint64_t old_size, uint64_t new_size);
void pmmFree(void * ptr, uint64_t size);

#endif