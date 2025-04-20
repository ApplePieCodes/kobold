#include <arch/x86_64/vmm.h>
#include <arch/x86_64/pmm.h>
#include <colors.h>
#include <math.h>
#include <stdio.h>
#include <bootloader.h>
#include <string.h>
#include <stdint.h>

page_table_t *kernelPagemap;

static uint64_t *getOrAllocateTable(uint64_t *parent, uint64_t index, uint8_t flags) {
    if (!(parent[index] & PRESENT_BIT)) {
        void *page = pmmAlloc(1);
        if (!page) {
            printf("[" BRED "VMM" WHT "] Failed to allocate page table\n");
            return NULL;
        }
        memset((void *)(hhdm_request.response->offset + (uint64_t)page), 0, 4096);
        parent[index] = (PAGE_ADDRESS((uint64_t)page) | flags | PRESENT_BIT | WRITABLE_BIT);
    }
    else {
        parent[index] |= flags;
    }
    return (uint64_t *)(hhdm_request.response->offset + PAGE_ADDRESS(parent[index]));
}

void vmmMapPage(uint64_t *pagemap, uint64_t virtualAddress, uint64_t physicalAddress, uint8_t flags) {
    uint64_t pml4Index = PAGE_INDEX(virtualAddress, PML4_SHIFT);
    uint64_t pml3Index = PAGE_INDEX(virtualAddress, PML3_SHIFT);
    uint64_t pml2Index = PAGE_INDEX(virtualAddress, PML2_SHIFT);
    uint64_t pml1Index = PAGE_INDEX(virtualAddress, PML1_SHIFT);

    uint64_t *pml3 = getOrAllocateTable(pagemap, pml4Index, flags);
    if (!pml3) return;
    
    uint64_t *pml2 = getOrAllocateTable(pml3, pml3Index, flags);
    if (!pml2) return;
    
    uint64_t *pml1 = getOrAllocateTable(pml2, pml2Index, flags);
    if (!pml1) return;

    pml1[pml1Index] = (physicalAddress & PAGE_MASK) | flags | PRESENT_BIT;    
}

void vmmLoadPagemap(uint64_t *map) {
    uint64_t phys_addr = (uint64_t)map - hhdm_request.response->offset;
    
    // Ensure interrupts are disabled
    asm volatile("cli");
    // Load CR3
    asm volatile("mov %0, %%cr3" :: "r"(phys_addr));
    asm volatile("sti");
}

void initVMM() {
    printf("[" BGRN "VMM" WHT "] Initializing VMM...\n");

    kernelPagemap = (page_table_t *)(hhdm_request.response->offset + (uint64_t)pmmAlloc(1));
    memset(kernelPagemap, 0, sizeof(page_table_t));
    
    struct limine_memmap_entry **memmap = memmap_request.response->entries;
    uint64_t memmap_entries = memmap_request.response->entry_count;
    for (uint64_t i = 0; i < memmap_entries; i++) // Clear usable pages
    {
        if (memmap[i]->type != LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE)
            continue;
        for (uint64_t j = 0; j < memmap[i]->length; j += PAGE_SIZE)
        {
            vmmMapPage((uint64_t *)kernelPagemap, memmap[i]->base + j + hhdm_request.response->offset, memmap[i]->base + j, PRESENT_BIT);
        }
    }

    extern char limineStart[], limineEnd[];

    uint64_t limineStartAligned = ALIGN_DOWN((uint64_t)&limineStart, PAGE_SIZE);
    uint64_t limineEndAligned = ALIGN_UP((uint64_t)&limineEnd, PAGE_SIZE);

    for (uint64_t i = limineStartAligned; i < limineEndAligned; i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - kernel_address_request.response->virtual_base + kernel_address_request.response->physical_base, PRESENT_BIT);
    }

    extern char textStart[], textEnd[];

    uint64_t textStartAligned = ALIGN_DOWN((uint64_t)&textStart, PAGE_SIZE);
    uint64_t textEndAligned = ALIGN_UP((uint64_t)&textEnd, PAGE_SIZE);

    for (uint64_t i = textStartAligned; i < textEndAligned; i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - kernel_address_request.response->virtual_base + kernel_address_request.response->physical_base, PRESENT_BIT);
    }

    extern char dataStart[], dataEnd[];

    uint64_t dataStartAligned = ALIGN_DOWN((uint64_t)&dataStart, PAGE_SIZE);
    uint64_t dataEndAligned = ALIGN_UP((uint64_t)&dataEnd, PAGE_SIZE);

    for (uint64_t i = dataStartAligned; i < dataEndAligned; i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - kernel_address_request.response->virtual_base + kernel_address_request.response->physical_base, PRESENT_BIT | WRITABLE_BIT);
    }

    extern char rodataStart[], rodataEnd[];

    uint64_t rodataStartAligned = ALIGN_DOWN((uint64_t)&rodataStart, PAGE_SIZE);
    uint64_t rodataEndAligned = ALIGN_UP((uint64_t)&rodataEnd, PAGE_SIZE);

    for (uint64_t i = rodataStartAligned; i < rodataEndAligned; i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - kernel_address_request.response->virtual_base + kernel_address_request.response->physical_base, PRESENT_BIT);
    }

    printf("[" BGRN "VMM" WHT "] Loading Page Map...\n");
    vmmLoadPagemap((uint64_t *)kernelPagemap);

    printf("[" BGRN "VMM" WHT "] VMM Initialized...\n");
}