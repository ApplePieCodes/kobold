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
    printf("[PMM] Initializing PMM...\n");
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
    printf("[PMM] PMM Initialized\n");
    printf("[PMM] FREE PAGES: %lu\n", free_pages);
}

static void* innerAlloc(uint64_t size, uint64_t limit) // Find a usable page
{
    uint64_t p = 0;
    while(last_used_index < limit)
    {
        if(!bitmapGet(last_used_index++))
        {
            if(++p == size)
            {
                uint64_t page = last_used_index - size;
                for (uint64_t i = page; i < last_used_index; i++) {
                    bitmapSet(i);
                }
                return (void*) (page * PAGE_SIZE);
            }
        }
        else 
        {
            p = 0;
        }
    }
    return NULL;
}

void* pmmAlloc(uint64_t size)
{
	spinlockLock(&pmmLock);
    uint64_t lui = last_used_index;
    void* ret = innerAlloc(size, highest_address / PAGE_SIZE);
    if (ret == NULL)
    {
        last_used_index = 0;
        ret = innerAlloc(size, lui);
    }
    
	free_pages -= size;
	spinlockUnlock(&pmmLock);
    return ret;
}

void* pmmAllocz(uint64_t size)
{
    void * ret = pmmAlloc(size);
    uint64_t * ptr = (uint64_t *)ret;

	for (uint64_t i = 0; i < (size * PAGE_SIZE) / 8; i++)
    {
        (ptr + hhdm_request.response->offset)[i] = 0;
    }

    return ret;
}

void* pmmRealloc(void * ptr, uint64_t old_size, uint64_t new_size)
{
    if (ptr == NULL)
        return pmmAlloc(new_size);

    if(new_size == 0)
    {
        pmmFree(ptr, old_size);
        return NULL;
    }
    if (new_size < old_size)
        old_size = new_size;

    void* realloc_ptr = pmmAlloc(new_size);
    memcpy((realloc_ptr + hhdm_request.response->offset), (ptr + hhdm_request.response->offset), old_size);
    pmmFree(ptr, old_size);

    return realloc_ptr;
}

/// @brief Free a physical region of memory
/// @param ptr The physical address of the memory being freed
/// @param size The size of the memory being freed
void pmmFree(void * ptr, uint64_t size)
{
	spinlockLock(&pmmLock);
    uint64_t page = (uint64_t)ptr / PAGE_SIZE;
    for(uint64_t i = page; i < page + size; i++) {
        bitmapClear(i);
    }
	free_pages += size;
	spinlockUnlock(&pmmLock);
}