#include <stdio.h>
#include <arch/x86_64/idt.h>
#include <colors.h>
#include <term/term.h>
#include <string.h>

static inline void panic(const char *reason, registers_t *regs) {
    int len = strlen("PANIC: ");
    len += strlen(reason);
    printf("PANIC: %s\n", reason);
    printf("CR0: %p  CR2: %p\n", regs->cr0, regs->cr2);
    printf("CR3: %p  CR4: %p\n", regs->cr3, regs->cr4);
    printf("CS: %p\n", regs->cs);
    printf("ERROR CODE: %p\n", regs->error_code);
    printf("RAX: %p  RBX: %p\n", regs->rax, regs->rbx);
    printf("RCX: %p  RDI: %p\n", regs->rcx, regs->rdi);
    printf("RDX: %p\n", regs->rdx);
    printf("R8: %p  R9: %p\n", regs->r8, regs->r9);
    printf("R10: %p  R11: %p\n", regs->r10, regs->r11);
    printf("R12: %p  R13: %p\n", regs->r12, regs->r13);
    printf("R14: %p  R15: %p\n", regs->r14, regs->r15);
    printf("RFLAGS: %p\n", regs->rflags);
    printf("RIP: %p\n", regs->rip);
    printf("RSI: %p\n", regs->rsi);
    printf("RSP: %p  RBP: %p\n", regs->rsp, regs->rbp);
    asm("cli");
    while (1) {

    }
}