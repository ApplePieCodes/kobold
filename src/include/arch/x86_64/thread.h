#include <stdint.h>

typedef struct thread {
    uint64_t rsp;
    uint64_t cr3;
    uint64_t process_id;
    uint64_t owner_id;
    struct thread *owner;
    
} thread_t;