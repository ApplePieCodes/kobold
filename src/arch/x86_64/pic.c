#include <arch/x86_64/cpu.h>
#include <arch/x86_64/pic.h>
#include <stdio.h>

void remapPIC(int offset1, int offset2) {
    printf("Remapping PIC...\n");
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, offset1); // Set the offset of IRQs 0-7
    io_wait();
    outb(PIC2_DATA, offset2); // Set the offset of IRQs 8-15
    io_wait();
    outb(PIC1_DATA, 0x04); // Tell Master PIC that there is a Slave PIC at IRQ2 (0000 0100)
    io_wait();
    outb(PIC2_DATA, 0x02); // Tell Slave PIC its cascade identity (0000 0010)
    io_wait();

    outb(PIC1_DATA, ICW4_8086); // Set 8086 mode for Master PIC
    io_wait();
    outb(PIC2_DATA, ICW4_8086); // Set 8086 mode for Slave PIC
    io_wait();

    outb(PIC1_DATA, 0xFF); // Disable all IRQs on Master PIC
    outb(PIC2_DATA, 0xFF); // Disable all IRQs on Slave PIC
    printf("PIC remapped.\n");
}

void sendEOI(int irq) {
    if (irq >= 8) {
        outb(PIC2_COMMAND, 0x20);
    }
    outb(PIC1_COMMAND, 0x20);
}

void disablePIC() {
    outb(PIC1_DATA, 0xFF); // Disable all IRQs on Master PIC
    outb(PIC2_DATA, 0xFF); // Disable all IRQs on Slave PIC
}

void enablePIC() {
    outb(PIC1_DATA, 0x00); // Enable all IRQs on Master PIC
    outb(PIC2_DATA, 0x00); // Enable all IRQs on Slave PIC
}

void disableIRQ(int irq) {
    if (irq < 8) {
        outb(PIC1_DATA, inb(PIC1_DATA) | (1 << irq));
    } else {
        outb(PIC2_DATA, inb(PIC2_DATA) | (1 << (irq - 8)));
    }
}

void enableIRQ(int irq) {
    if (irq < 8) {
        outb(PIC1_DATA, inb(PIC1_DATA) & ~(1 << irq));
    } else {
        outb(PIC2_DATA, inb(PIC2_DATA) & ~(1 << (irq - 8)));
    }
}