#include <stdint.h>

#define THREAD_COPY_CR3 0b00000001

typedef struct thread {
    uint64_t rsp;
    uint64_t rip;
    uint64_t cr3;
    uint64_t process_id;
    uint64_t owner_id;
    struct thread *owner;
    struct thread *next;
} thread_t;

typedef struct threadContext {
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15;
};

/// @brief Returns 0 if thread creation fails
/// @param threadFlags The flags to use when creating this thread
/// @return The PID of the created thread
uint64_t createThread(int threadFlags, void (*entryPoint)(void));

void killThread(uint64_t pid);