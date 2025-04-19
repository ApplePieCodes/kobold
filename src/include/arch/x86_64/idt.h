#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IST_OFFSET_0 0b0000000000000000
#define IST_OFFSET_1 0b0000000000000001
#define IST_OFFSET_2 0b0000000000000010
#define IST_OFFSET_3 0b0000000000000011
#define INTERUPT_GATE 0b0000111000000000
#define TRAP_GATE 0b0000111100000000
#define IDT_RING_0 0b0000000000000000
#define IDT_RING_1 0b0010000000000000
#define IDT_RING_2 0b0100000000000000
#define IDT_RING_3 0b0110000000000000
#define IDT_PRESENT 0b1000000000000000

typedef struct idtr {
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) idtr_t;

typedef struct idt_entry {
    uint16_t offset0;
    uint16_t segment_selector;
    uint16_t flags;
    uint16_t offset1;
    uint32_t offset2;
    uint32_t reserved;
} __attribute__((packed)) idt_entry_t;

typedef struct registers {
    uint64_t cr4;
    uint64_t cr3;
    uint64_t cr2;
    uint64_t cr0;
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rbp;
    uint64_t rbx;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rax;
    uint64_t interrupt_number;
    uint64_t error_code;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
} __attribute__((packed)) registers_t;

void initIDT();

#endif