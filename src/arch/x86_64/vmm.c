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
    
    // Allocate kernel page map
    void *page = pmmAlloc(1);
    kernelPagemap = (page_table_t *)(hhdm_request.response->offset + (uint64_t)page);
    memset(kernelPagemap, 0, sizeof(page_table_t));

    // First, identity map the first 4GB of physical memory (needed for boot environment)
    printf("[" BGRN "VMM" WHT "] Identity mapping first 4GB...\n");
    for(uint64_t i = 0; i < 0x100000000; i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i, PRESENT_BIT | WRITABLE_BIT);
    }

    // Map the higher half direct mapping (needed for physical memory access)
    printf("[" BGRN "VMM" WHT "] Mapping higher half direct map...\n");
    for(uint64_t i = 0; i < 0x100000000; i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, hhdm_request.response->offset + i, i, PRESENT_BIT | WRITABLE_BIT);
    }

    // Map the current stack (very important!)
    printf("[" BGRN "VMM" WHT "] Mapping stack...\n");
    uint64_t stack_pointer;
    asm volatile("mov %%rsp, %0" : "=r"(stack_pointer));
    for(int i = -16; i <= 16; i++) {
        uint64_t stack_page = ALIGN_DOWN(stack_pointer + i * PAGE_SIZE, PAGE_SIZE);
        vmmMapPage((uint64_t *)kernelPagemap, stack_page, stack_page - hhdm_request.response->offset, PRESENT_BIT | WRITABLE_BIT);
    }

    // Map Limine structures
    printf("[" BGRN "VMM" WHT "] Mapping Limine Memory...\n");
    extern uint64_t limineStart, limineEnd;
    for (uint64_t i = ALIGN_DOWN((uint64_t)&limineStart, PAGE_SIZE); i < ALIGN_UP((uint64_t)&limineEnd, PAGE_SIZE); i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - hhdm_request.response->offset, PRESENT_BIT | WRITABLE_BIT);
    }
    
    // Map bootloader reclaimable memory
    struct limine_memmap_entry **memmap = memmap_request.response->entries;
    uint64_t memmap_entries = memmap_request.response->entry_count;
    for (uint64_t i = 0; i < memmap_entries; i++) {
        if (memmap[i]->type != LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE)
            continue;
        for (uint64_t j = 0; j < memmap[i]->length; j += PAGE_SIZE) {
            vmmMapPage((uint64_t *)kernelPagemap, memmap[i]->base + j, (memmap[i]->base + j) - hhdm_request.response->offset, PRESENT_BIT | WRITABLE_BIT);
        }
    }
    printf("[" BGRN "VMM" WHT "] Limine Memory Mapped\n");

    // Map kernel sections
    printf("[" BGRN "VMM" WHT "] Mapping Text Memory...\n");
    extern uint64_t textStart, textEnd; 
    for (uint64_t i = ALIGN_DOWN((uint64_t)&textStart, PAGE_SIZE); i < ALIGN_UP((uint64_t)&textEnd, PAGE_SIZE); i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - hhdm_request.response->offset, PRESENT_BIT);
    }
    printf("[" BGRN "VMM" WHT "] Text Memory Mapped\n");

    printf("[" BGRN "VMM" WHT "] Mapping Rodata Memory...\n");
    extern uint64_t rodataStart, rodataEnd; 
    for (uint64_t i = ALIGN_DOWN((uint64_t)&rodataStart, PAGE_SIZE); i < ALIGN_UP((uint64_t)&rodataEnd, PAGE_SIZE); i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - hhdm_request.response->offset, PRESENT_BIT);
    }
    printf("[" BGRN "VMM" WHT "] Rodata Memory Mapped\n");

    printf("[" BGRN "VMM" WHT "] Mapping Data Memory...\n");
    extern uint64_t dataStart, dataEnd; 
    for (uint64_t i = ALIGN_DOWN((uint64_t)&dataStart, PAGE_SIZE); i < ALIGN_UP((uint64_t)&dataEnd, PAGE_SIZE); i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - hhdm_request.response->offset, PRESENT_BIT | WRITABLE_BIT);
    }
    printf("[" BGRN "VMM" WHT "] Data Memory Mapped\n");

    // Map the kernel page map itself (self-referencing)
    printf("[" BGRN "VMM" WHT "] Self-mapping kernel page map...\n");
    vmmMapPage((uint64_t *)kernelPagemap, (uint64_t)kernelPagemap, (uint64_t)page, PRESENT_BIT | WRITABLE_BIT);

    printf("[" BGRN "VMM" WHT "] Loading Page Map...\n");
    vmmLoadPagemap((uint64_t *)kernelPagemap);

    printf("[" BGRN "VMM" WHT "] VMM Initialized...\n");
}