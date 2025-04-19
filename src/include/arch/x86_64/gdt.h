#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stdio.h>
#include <colors.h>

#define GDT_ACCESS_PRESENT 0b10000000 // Segment is present
#define GDT_ACCESS_RING_0 0b00000000
#define GDT_ACCESS_RING_1 0b01000000
#define GDT_ACCESS_RING_2 0b00100000
#define GDT_ACCESS_RING_3 0b01100000
#define GDT_ACCESS_DESCRIPTOR_TYPE 0b00010000 // Set for code/data, clear for system
#define GDT_ACCESS_EXECUTABLE 0b00001000 // Is executable (code segment)
#define GDT_ACCESS_GROW_DOWN 0b00000100 // Does the segment grow down
#define GDT_ACCESS_READABLE 0b00000010 // Is readable (code segment)
#define GDT_ACCESS_WRITEABLE 0b00000010 // Is writable (data segment)
#define GDT_ACCESS_ACCESSED 0b00000001 // Segment is accessed

#define GDT_KERNEL_CODE_SEGMENT 0x08
#define GDT_KERNEL_DATA_SEGMENT 0x10
#define GDT_USER_CODE_SEGMENT 0x18
#define GDT_USER_DATA_SEGMENT 0x20

#define GDT_FLAG_LONG_MODE_CODE 0b0010
#define GDT_FLAG_SIZE_PROTECTED_MODE 0b0100
#define GDT_FLAG_GRANULARITY 0b1000

#define GDT BGRN "GDT" WHT

/// @brief An entry in the GDT
typedef struct gdt_entry {
    uint16_t limit0;
    uint16_t base0;
    uint8_t base1;
    uint8_t access;
    uint8_t limit1_flags;
    uint8_t base2;
} __attribute__((packed)) gdt_entry_t;

/// @brief The Global Descriptor Table
typedef struct gdt {
    gdt_entry_t null_segment;
    gdt_entry_t kernel_code_segment;
    gdt_entry_t kernel_data_segment;
    gdt_entry_t user_code_segment;
    gdt_entry_t user_data_segment;
} __attribute__((packed)) gdt_t;

/// @brief The GDT Descriptor
typedef struct gdtr
{
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) gdtr_t;

/// @brief Initialize the GDT
void initGDT();

#endif