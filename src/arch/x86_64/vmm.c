// The Kobold Kernel

// src/arch/x86_64/vmm.c

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

//TODO: Add support for 5-level paging
//TODO: Heap Allocator

#include <arch/x86_64/vmm.h>

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

void vmmUnmapPage(uint64_t *pagemap, uint64_t virtualAddress) {
    uint64_t pml4Index = PAGE_INDEX(virtualAddress, PML4_SHIFT);
    uint64_t pml3Index = PAGE_INDEX(virtualAddress, PML3_SHIFT);
    uint64_t pml2Index = PAGE_INDEX(virtualAddress, PML2_SHIFT);
    uint64_t pml1Index = PAGE_INDEX(virtualAddress, PML1_SHIFT);

    uint64_t *pml3 = (uint64_t *)(hhdm_request.response->offset + PAGE_ADDRESS(pagemap[pml4Index]));
    if (!pml3) return;
    
    uint64_t *pml2 = (uint64_t *)(hhdm_request.response->offset + PAGE_ADDRESS(pml3[pml3Index]));
    if (!pml2) return;
    
    uint64_t *pml1 = (uint64_t *)(hhdm_request.response->offset + PAGE_ADDRESS(pml2[pml2Index]));
    if (!pml1) return;

    pml1[pml1Index] = 0;
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
        for (uint64_t j = 0; j < memmap[i]->length; j += PAGE_SIZE)
        {
            vmmMapPage((uint64_t *)kernelPagemap, memmap[i]->base + j + hhdm_request.response->offset, memmap[i]->base + j, PRESENT_BIT | WRITABLE_BIT);
        }
    }

    extern char limineStart[], limineEnd[];

    uint64_t limineStartAligned = ALIGN_DOWN((uint64_t)&limineStart, PAGE_SIZE);
    uint64_t limineEndAligned = ALIGN_UP((uint64_t)&limineEnd, PAGE_SIZE);

    for (uint64_t i = limineStartAligned; i < limineEndAligned; i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - kernel_address_request.response->virtual_base + kernel_address_request.response->physical_base, PRESENT_BIT | WRITABLE_BIT);
    }

    extern char textStart[], textEnd[];

    uint64_t textStartAligned = ALIGN_DOWN((uint64_t)&textStart, PAGE_SIZE);
    uint64_t textEndAligned = ALIGN_UP((uint64_t)&textEnd, PAGE_SIZE);

    for (uint64_t i = textStartAligned; i < textEndAligned; i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - kernel_address_request.response->virtual_base + kernel_address_request.response->physical_base, PRESENT_BIT);
    }

    uint64_t bitmapStartAligned = ALIGN_DOWN((uint64_t)bitmap, PAGE_SIZE);
    uint64_t bitmapEndAligned = ALIGN_UP((uint64_t)bitmap + bitmap_size, PAGE_SIZE);

    for (uint64_t i = bitmapStartAligned; i < bitmapEndAligned; i += PAGE_SIZE) {
        vmmMapPage((uint64_t *)kernelPagemap, i, i - hhdm_request.response->offset, PRESENT_BIT | WRITABLE_BIT);
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

bool isPageMapped(uint64_t vaddr) {
    uint64_t pml4_index = (vaddr >> 39) & 0x1FF;
    uint64_t pdpt_index = (vaddr >> 30) & 0x1FF;
    uint64_t pd_index   = (vaddr >> 21) & 0x1FF;
    uint64_t pt_index   = (vaddr >> 12) & 0x1FF;

    if (!(*kernelPagemap[pml4_index] & PRESENT_BIT)) return false;
    uint64_t *pdpt = (uint64_t *)(hhdm_request.response->offset + PAGE_ADDRESS(*kernelPagemap[pml4_index]));

    if (!(pdpt[pdpt_index] & PRESENT_BIT)) return false;
    uint64_t *pd = (uint64_t *)(hhdm_request.response->offset + PAGE_ADDRESS(pdpt[pdpt_index]));

    if (!(pd[pd_index] & PRESENT_BIT)) return false;

    uint64_t *pt = (uint64_t *)(hhdm_request.response->offset + PAGE_ADDRESS(pd[pd_index]));

    return pt[pt_index] & PRESENT_BIT;
}

void *findFreeRegion(size_t size) {
    uint64_t currentRunStart = 0;
    uint64_t currentRunLength = 0;

    for (uint64_t i = 0x1000; i < 0xFFFFFFFFFFFFF000; i += PAGE_SIZE) {
        if (isPageMapped(i)) {
            currentRunLength = 0;
            currentRunStart = 0;
        }
        else {
            currentRunStart = i;
            while (isPageMapped(i) == false && i < 0xFFFFFFFFFFFFF000) {
                currentRunLength += PAGE_SIZE;
                i += PAGE_SIZE;
                if (currentRunLength >= size) {
                    return (void *)currentRunStart;
                }
            }
        }
    }
}

/// @brief Get a chunk of memory of the requested size and map it to the requested address, if not null
/// @param requestedAddress The address to map the memory to, or NULL for any address
/// @param size The size of the memory to allocate in pages.
void *vmmGetPage(uint64_t *requestedAddress, size_t size) {
    if (requestedAddress == NULL) {
        void *mem = pmmAlloc(size);
        if (!mem) {
            printf("[" BRED "VMM" WHT "] Failed to allocate memory\n");
            return NULL;
        }
        void *freeRegion = findFreeRegion(size * PAGE_SIZE);
        if (!freeRegion) {
            printf("[" BRED "VMM" WHT "] Failed to find free region\n");
            pmmFree(mem, size);
            return NULL;
        }
        for (size_t i = 0; i < size; i++) {
            vmmMapPage((uint64_t *)kernelPagemap, (uint64_t)freeRegion + (i * PAGE_SIZE), (uint64_t)mem + (i * PAGE_SIZE), PRESENT_BIT | WRITABLE_BIT);
        }
        return freeRegion;
    }
    else {
        uint64_t pml4Index = PAGE_INDEX((uint64_t)requestedAddress, PML4_SHIFT);
        uint64_t pml3Index = PAGE_INDEX((uint64_t)requestedAddress, PML3_SHIFT);
        uint64_t pml2Index = PAGE_INDEX((uint64_t)requestedAddress, PML2_SHIFT);
        uint64_t pml1Index = PAGE_INDEX((uint64_t)requestedAddress, PML1_SHIFT);

        uint64_t *pml3 = getOrAllocateTable((uint64_t *)kernelPagemap, pml4Index, PRESENT_BIT | WRITABLE_BIT);
        if (!pml3) return NULL;
        
        uint64_t *pml2 = getOrAllocateTable(pml3, pml3Index, PRESENT_BIT | WRITABLE_BIT);
        if (!pml2) return NULL;
        
        uint64_t *pml1 = getOrAllocateTable(pml2, pml2Index, PRESENT_BIT | WRITABLE_BIT);
        if (!pml1) return NULL;

        if (pml1[pml1Index] & PRESENT_BIT) {
            printf("[" BRED "VMM" WHT "] Memory already allocated at requested address\n");
            return NULL;
        }
        return (void *)requestedAddress;
    }
}

void vmmDropPage(uint64_t *address, size_t size) {
    uint64_t pml4Index = PAGE_INDEX((uint64_t)address, PML4_SHIFT);
    uint64_t pml3Index = PAGE_INDEX((uint64_t)address, PML3_SHIFT);
    uint64_t pml2Index = PAGE_INDEX((uint64_t)address, PML2_SHIFT);
    uint64_t pml1Index = PAGE_INDEX((uint64_t)address, PML1_SHIFT);

    uint64_t *pml3 = getOrAllocateTable((uint64_t *)kernelPagemap, pml4Index, PRESENT_BIT);
    
    uint64_t *pml2 = getOrAllocateTable(pml3, pml3Index, PRESENT_BIT);
    
    uint64_t *pml1 = getOrAllocateTable(pml2, pml2Index, PRESENT_BIT);

    
    for (uint64_t i = 0; i < size; i += 4096) {
        pmmFree((void *)(PAGE_ADDRESS(pml1[pml1Index])), 1);
        vmmUnmapPage((uint64_t *)kernelPagemap, (uint64_t)address + i);
        pml1Index++;
    }
}