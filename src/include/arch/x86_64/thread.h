#include <stdint.h>

typedef struct threadState {
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t rip;
    uint64_t cs, ds, ss, es, fs, gs;
    uint64_t rflags;
    uint64_t vmmap;
    uint64_t virtualStack;
} threadState_t;