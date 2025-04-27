#include <keyboard.h>

volatile keypress_t keypressQueue[256];
uint64_t keypressQueueHead = 0;
uint64_t keypressQueueTail = 0;

void keyboardPushKey(key_t k, uint8_t modifiers) {
    uint64_t nextTail = (keypressQueueTail + 1) % 256;
    if (nextTail != keypressQueueHead) { // Check for overflow
        keypressQueue[keypressQueueTail].key = k;
        keypressQueue[keypressQueueTail].modifiers = modifiers;
        keypressQueueTail = nextTail;
    }
}

keypress_t keyboardReadKey() {
    while (keypressQueueHead == keypressQueueTail) {
        // Wait for a key to be pressed
    }

    keypress_t keypress = keypressQueue[keypressQueueHead];
    keypressQueueHead = (keypressQueueHead + 1) % 256;
    return keypress;
}
