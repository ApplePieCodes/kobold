// The Kobold Kernel

// src/arch/x86_64/init.c

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

#include <term/term.h>
#include <arch/x86_64/gdt.h>
#include <arch/x86_64/pmm.h>
#include <arch/x86_64/vmm.h>
#include <arch/x86_64/idt.h>
#include <stdio.h>

void init() {
    initTerm();
    initGDT();
    initPMM();
    initIDT();
    initVMM();
    printf("Got memory at %d\n", (uint64_t)vmmGetPage(NULL, 1));
    printf("Got memory at %d\n", (uint64_t)vmmGetPage(NULL, 1));
    vmmDropPage((uint64_t *)4096, 1);
    printf("Got memory at %d\n", (uint64_t)vmmGetPage(NULL, 1));
    

    while (1) {
        
    }
}