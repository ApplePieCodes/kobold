#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <term/term.h>
#include <arch/x86_64/pmm.h>
#include <spinlock.h>
#include <bootloader.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static uint8_t *bitmap;
spinlock_t pmmLock;
uint64_t highest_address;
uint64_t bitmap_size;
uint64_t free_pages;
uint64_t last_used_index;

void bitmapSet(size_t index) {
    bitmap[index / 8] |= (1 << (index % 8));
}

void bitmapClear(size_t index) {
    bitmap[index / 8] &= ~(1 << (index % 8));
}

bool bitmapGet(size_t index) {
    return bitmap[index / 8] & (1 << (index % 8));
}

void initPMM() {
    printf("[KOBOLD] Initializing PMM...\n");
    spinlockLock(&pmmLock);

    struct limine_memmap_entry **memmap = memmap_request.response->entries;
    uint64_t memmap_entries = memmap_request.response->entry_count;

    for (uint64_t i = 0; i < memmap_entries; i++) { // Get Bitmap Size
        if (memmap[i]->type != LIMINE_MEMMAP_USABLE && memmap[i]->type != LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
            continue;
        }

        uint64_t top_address = memmap[i]->base + memmap[i]->length;

        if (top_address > highest_address) {
            highest_address = top_address;
        }
    }
    bitmap_size = ALIGN_UP((highest_address / PAGE_SIZE) / 8, PAGE_SIZE);

    for (uint64_t i = 0; i < memmap_entries; i++) // Find somewhere to allocate the bitmap
    {
        if (memmap[i]->type != LIMINE_MEMMAP_USABLE)
            continue;
        if (memmap[i]->length >= bitmap_size)
        {
            bitmap = (uint8_t *)(memmap[i]->base + hhdm_request.response->offset);

            memset(bitmap, 0xFF, bitmap_size);

            memmap[i]->length -= bitmap_size;
            memmap[i]->base += bitmap_size;

            break;
        }
    }

    for (uint64_t i = 0; i < memmap_entries; i++) // Clear usable pages
    {
        if (memmap[i]->type != LIMINE_MEMMAP_USABLE)
            continue;
        for (uint64_t j = 0; j < memmap[i]->length; j += PAGE_SIZE)
        {
			free_pages++;
            bitmapClear((memmap[i]->base + j) / PAGE_SIZE);
        }
    }

    spinlockUnlock(&pmmLock);
    printf("[KOBOLD] PMM Initialized\n");
    printf("[KOBOLD] FREE PAGES: %d\n", free_pages);
}