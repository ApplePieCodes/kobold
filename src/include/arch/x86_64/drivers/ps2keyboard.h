#include <stdbool.h>

void ps2KeyboardHandler();

typedef struct keyboardState {
    bool shiftPressed;
    bool ctrlPressed;
    bool altPressed;
    bool superPressed;
} keyboardState_t;