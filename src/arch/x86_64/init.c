// The Kobold Kernel

// src/arch/x86_64/init.c
// April 2025

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

#include <term/term.h>
#include <arch/x86_64/gdt.h>
#include <arch/x86_64/pmm.h>
#include <arch/x86_64/vmm.h>
#include <arch/x86_64/idt.h>
#include <stdio.h>

extern void stage2Forwarder(uint64_t stack_base);

void init() {
    initTerm();
    initGDT();
    initPMM();
    initIDT();
    initVMM();
    uint64_t stackPtr = (uint64_t)pmmAlloc(4); // Allocate 4 pages (16 KB)
    stage2Forwarder(stackPtr);
}

void initStage2() {
    printf("Hit Stage 2!");

    while (1) {

    }
}