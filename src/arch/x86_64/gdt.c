// The Kobold Kernel

// src/arch/x86_64/gdt.c
// April 2025

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

#include <arch/x86_64/gdt.h>
#include <colors.h>

gdt_t gdt;

void gdtSetGate(gdt_entry_t *entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    // First 16 bits of limit
    entry->limit0 = limit & 0xFFFF;
    // Last 4 bits of limit
    entry->limit1_flags = (limit >> 16) & 0x0F;

    // First 16 bits of base
    entry->base0 = base & 0xFFFF;
    // Middle 8 bits of base
    entry->base1 = (base >> 16) & 0xFF;
    // Last 8 bits of base
    entry->base2 = (base >> 24) & 0xFF;

    entry->access = access;

    // Put this in the empty space
    entry->limit1_flags |= (flags << 4);
}

gdtr_t setupGdtr() {
    gdtr_t gdtr;
    gdtr.size = sizeof(gdt_t) - 1;
    gdtr.offset = (uint64_t)&gdt;
    return gdtr;
}

/// @brief set the segment registers
void setSegmentRegisters() {
    //TODO: Set CS
    asm("mov %0, %%ax" : : "r"((uint16_t)GDT_KERNEL_DATA_SEGMENT));
    asm("mov %ax, %ds");
    asm("mov %ax, %es");
    asm("mov %ax, %ss");
    asm("mov %ax, %fs");
    asm("mov %ax, %gs");
}


extern void loadCS();

void loadGDT(gdtr_t gdtr) {
    asm("lgdt %0\n" : : "m"(gdtr));
    loadCS();
    setSegmentRegisters();
}

void initGDT() {
    printf("[" GDT "] Initializing GDT...\n");
    gdtSetGate(&gdt.null_segment, 0, 0, 0, 0);
    printf("[" GDT "] Set Null Segment\n");

    gdtSetGate(&gdt.kernel_code_segment, 0, 0xFFFFF, 
        GDT_ACCESS_PRESENT | GDT_ACCESS_RING_0 | GDT_ACCESS_EXECUTABLE | 
        GDT_ACCESS_READABLE | GDT_ACCESS_ACCESSED | GDT_ACCESS_DESCRIPTOR_TYPE, 
        GDT_FLAG_LONG_MODE_CODE | GDT_FLAG_GRANULARITY);
    printf("[" GDT "] Set Kernel Code Segment\n");
        
    gdtSetGate(&gdt.kernel_data_segment, 0, 0xFFFFF,
        GDT_ACCESS_PRESENT | GDT_ACCESS_RING_0 | GDT_ACCESS_GROW_DOWN | 
        GDT_ACCESS_WRITEABLE | GDT_ACCESS_ACCESSED | GDT_ACCESS_DESCRIPTOR_TYPE,
        GDT_FLAG_SIZE_PROTECTED_MODE | GDT_FLAG_GRANULARITY);
        printf("[" GDT "] Set Kernel Data Segment\n");

    gdtSetGate(&gdt.user_code_segment, 0, 0xFFFFF,
        GDT_ACCESS_PRESENT | GDT_ACCESS_RING_3 | GDT_ACCESS_EXECUTABLE | 
        GDT_ACCESS_READABLE | GDT_ACCESS_ACCESSED, 
        GDT_FLAG_LONG_MODE_CODE | GDT_FLAG_GRANULARITY);
        printf("[" GDT "] Set User Code Segment\n");

    gdtSetGate(&gdt.user_data_segment, 0, 0xFFFFF,
        GDT_ACCESS_PRESENT | GDT_ACCESS_RING_0 | GDT_ACCESS_GROW_DOWN | 
        GDT_ACCESS_WRITEABLE | GDT_ACCESS_ACCESSED,
        GDT_FLAG_SIZE_PROTECTED_MODE | GDT_FLAG_GRANULARITY);
    printf("[" GDT "] Set User Data Segment\n");

    gdtr_t gdtr = setupGdtr();

    loadGDT(gdtr);
    printf("[" GDT "] GDT Initialized\n");
}