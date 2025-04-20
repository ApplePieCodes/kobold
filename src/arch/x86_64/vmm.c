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
        memset((void *)(hhdm_request.response->offset + (uint64_t)page), 0, 4096);
        parent[index] = (PAGE_ADDRESS((uint64_t)page) | flags);
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
    uint64_t *pml2 = getOrAllocateTable(pml3, pml3Index, flags);
    uint64_t *pml1 = getOrAllocateTable(pml2, pml2Index, flags);

    pml1[pml1Index] = (physicalAddress & PAGE_MASK) | flags;    
}

void vmmLoadPagemap(uint64_t *map) {
    asm("movq %0, %%cr3" : : "r"((uint64_t)(map - hhdm_request.response->offset)) : "rax");
}

void initVMM() {
    printf("[" BGRN "VMM" WHT "] Initializing VMM...\n");
    kernelPagemap = (page_table_t *)(hhdm_request.response->offset + (uint64_t)pmmAlloc(1));
    memset(kernelPagemap, 0, sizeof(page_table_t));

    printf("[" BGRN "VMM" WHT "] Mapping Limine Memory...\n");
    extern uint64_t limineStart, limineEnd;
    for (uint64_t i = ALIGN_DOWN((uint64_t)&limineStart, PAGE_SIZE); i < ALIGN_UP((uint64_t)&limineEnd, PAGE_SIZE); i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - hhdm_request.response->offset, PRESENT_BIT);
    }
    printf("[" BGRN "VMM" WHT "] Limine Memory Mapped\n");

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
    for (uint64_t i = (uint64_t)&dataStart; i < (uint64_t)&dataEnd; i += 4096) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - hhdm_request.response->offset, PRESENT_BIT | WRITABLE_BIT | WRITETHROUGH_BIT);
    }
    printf("[" BGRN "VMM" WHT "] Data Memory Mapped\n");

    printf("[" BGRN "VMM" WHT "] Loading Page Map...\n");

    vmmLoadPagemap((uint64_t *)kernelPagemap);

    printf("[" BGRN "VMM" WHT "] VMM Initialized`...\n");
}