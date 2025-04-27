#include <arch/x86_64/thread.h>
#include <arch/x86_64/vmm.h>
#include <math.h>

//TODO: Multithreading support

thread_t *thread_list;
thread_t *current_thread;

void initThreading() { // We only initialize threading. No actual threads will be created until kernel init stage 2. Where we will pass on the VMM and Make a new stack.
    
}

uint64_t createThread(int threadFlags, void (*entryPoint)(void)) {
    thread_t *thread = vmmGetPage(NULL, ALIGN_UP(sizeof(thread_t)));
    
    if (threadFlags & THREAD_COPY_CR3) {
        asm("mov %%cr3, %0" : : "r"(thread->cr3)); // Get the value of CR3 (page table phys address.)
    }

    thread->owner = current_thread;
    thread->owner_id = thread->owner->process_id;
    thread->rip = entryPoint;
    //TODO: thread->rsp = allocateStack(16); // 64 KB stack. 16 pages.

    static uint64_t next_process_id = 1;

    // Find an unused process ID
    while (1) {
        thread_t *iter = thread_list;
        int is_used = 0;

        while (iter) {
            if (iter->process_id == next_process_id) {
                is_used = 1;
                break;
            }
            iter = iter->next;
        }

        if (!is_used) {
            thread->process_id = next_process_id++;
            break;
        }

        next_process_id++;
    }

    {
        thread_t *iter = thread_list;
        
        while (iter->next != NULL) {
            iter = iter->next;
        }
        iter->next = thread;
    }

    return thread;
}