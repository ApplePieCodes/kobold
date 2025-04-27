#include <stdbool.h>

void ps2KeyboardHandler();

void readLine(char *buffer);

typedef struct keyboardState {
    bool shiftPressed;
} keyboardState_t;