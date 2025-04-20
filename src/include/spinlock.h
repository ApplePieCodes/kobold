// The Kobold Kernel

// src/include/spinlock.h

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

#ifndef SPINLOCK_H
#define SPINLOCK_H

typedef struct spinlock
{
    int locked;
} spinlock_t;

static inline void spinlockLock(spinlock_t *lock) {
    while (lock->locked) {

    }
    lock->locked = 1;
}

static inline void spinlockUnlock(spinlock_t *lock) {
    lock->locked = 0;
}

#endif