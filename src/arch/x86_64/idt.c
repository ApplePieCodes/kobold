// The Kobold Kernel

// src/arch/x86_64/idt.c

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

#include <arch/x86_64/idt.h>
#include <arch/x86_64/pic.h>
#include <arch/x86_64/drivers/ps2keyboard.h>

idt_entry_t idt[256];

/// @brief Sets an IDT Gate
/// @param gate The gate to set
/// @param offset The Address of the handler
/// @param segment The segment to run it in
/// @param flags The flags to apply
void setIDTGate(uint16_t gate, uint64_t offset, uint16_t segment, uint16_t flags) {
    idt[gate].flags = flags;
    idt[gate].segment_selector = segment;
    idt[gate].offset0 = offset & 0xFFFF;
    idt[gate].offset1 = (offset >> 16) & 0xFFFF;
    idt[gate].offset2 = (offset >> 32) & 0xFFFFFFFF;
}

/// @brief Creates an IDT Descriptor and loads it
void loadIDT() {
    idtr_t idtd;
    idtd.size = sizeof(idt_entry_t[256]);
    idtd.offset = (uint64_t)&idt;
    asm("lidt %0" : : "m"(idtd));
}

extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();
extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();
extern void isr_32();
extern void isr_33();

void initIDT() {
    asm("cli");

    /// Disable PIC1
    outb(0x0021, 0xff);
    /// Disable PIC2
    outb(0x00A1, 0xff);

    printf("[" BGRN "IDT" WHT "] Initializing IDT...\n");
    setIDTGate(0, (uint64_t)isr_0, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(1, (uint64_t)isr_1, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(2, (uint64_t)isr_2, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(3, (uint64_t)isr_3, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(5, (uint64_t)isr_5, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(6, (uint64_t)isr_0, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(7, (uint64_t)isr_1, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(8, (uint64_t)isr_2, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(9, (uint64_t)isr_1, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(10, (uint64_t)isr_10, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(11, (uint64_t)isr_11, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(12, (uint64_t)isr_12, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(13, (uint64_t)isr_13, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(14, (uint64_t)isr_14, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(15, (uint64_t)isr_15, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(16, (uint64_t)isr_16, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(17, (uint64_t)isr_17, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(18, (uint64_t)isr_18, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(19, (uint64_t)isr_19, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(20, (uint64_t)isr_20, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(21, (uint64_t)isr_21, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(22, (uint64_t)isr_22, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(23, (uint64_t)isr_23, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(24, (uint64_t)isr_24, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(25, (uint64_t)isr_25, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(26, (uint64_t)isr_26, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(27, (uint64_t)isr_27, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(28, (uint64_t)isr_28, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(29, (uint64_t)isr_29, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(30, (uint64_t)isr_30, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(31, (uint64_t)isr_31, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(32, (uint64_t)isr_32, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);
    setIDTGate(33, (uint64_t)isr_33, 0x08, INTERUPT_GATE | IDT_RING_3 | IDT_PRESENT);


    remapPIC(0x20, 0x28); // Remap PIC1 to 32 and PIC2 to 40

    loadIDT();
    asm("sti");

    enableIRQ(0);
    enableIRQ(1);

    printf("[" BGRN "IDT" WHT "] IDT Initialized\n");
}

void isr_common_handler_c(registers_t *regs) {
    if (regs->interrupt_number == 0) {
        panic("Divide By 0", regs);
    }
    else if (regs->interrupt_number == 1) {
        // Debug
    }
    else if (regs->interrupt_number == 2) {
        panic("Non-Maskable Interrupt", regs);
    }
    else if (regs->interrupt_number == 3) {
        // Breakpoint
    }
    else if (regs->interrupt_number == 4) {
        panic("INTO Overflow", regs);
    }
    else if (regs->interrupt_number == 5) {
        panic("BOUND Overflow", regs);
    }
    else if (regs->interrupt_number == 6) {
        panic("Invalid OPCode", regs);
    }
    else if (regs->interrupt_number == 7) {
        panic("Device Not Avalible", regs);
    }
    else if (regs->interrupt_number == 8) {
        panic("Double Fault", regs);
    }
    else if (regs->interrupt_number == 9) {
        panic("LEGACY: Coprocessor Segment Overrun", regs);
    }
    else if (regs->interrupt_number == 10) {
        panic("Invalid TSS", regs);
    }
    else if (regs->interrupt_number == 11) {
        panic("Segment Not Present", regs);
    }
    else if (regs->interrupt_number == 12) {
        panic("Stack Segment Fault", regs);
    }
    else if (regs->interrupt_number == 13) {
        panic("General Protection Fault", regs);
    }
    else if (regs->interrupt_number == 14) {
        panic("Page Fault", regs);
    }
    else if (regs->interrupt_number == 15) {
        panic("Reserved", regs);
    }
    else if (regs->interrupt_number == 16) {
        panic("x87 Floating-Point Exception", regs);
    }
    else if (regs->interrupt_number == 17) {
        panic("Alignment Check", regs);
    }
    else if (regs->interrupt_number == 18) {
        panic("Machine Check", regs);
    }
    else if (regs->interrupt_number == 19) {
        panic("SIMD Floating Point Exception", regs);
    }
    else if (regs->interrupt_number == 20) {
        panic("Virtualization Exception", regs);
    }
    else if (regs->interrupt_number == 21) {
        panic("Control Protection Exception", regs);
    }
    else if (regs->interrupt_number == 22) {
        panic("Reserved", regs);
    }
    else if (regs->interrupt_number == 23) {
        panic("Reserved", regs);
    }
    else if (regs->interrupt_number == 24) {
        panic("Reserved", regs);
    }
    else if (regs->interrupt_number == 25) {
        panic("Reserved", regs);
    }
    else if (regs->interrupt_number == 26) {
        panic("Reserved", regs);
    }
    else if (regs->interrupt_number == 27) {
        panic("Reserved", regs);
    }
    else if (regs->interrupt_number == 28) {
        panic("Hypervisor Injection Exception", regs);
    }
    else if (regs->interrupt_number == 29) {
        panic("VMM Communication Exception", regs);
    }
    else if (regs->interrupt_number == 30) {
        panic("Security Exception", regs);
    }
    else if (regs->interrupt_number == 31) {
        panic("Reserved", regs);
    }
    else if (regs->interrupt_number == 32) {
        // TODO: Handle timer interrupt
        sendEOI(0x00);
    }
    else if (regs->interrupt_number == 33) {
        ps2KeyboardHandler();
        sendEOI(0x01);
    }
}