#include <stdint.h>
#include <arch/x86_64/drivers/ps2keyboard.h>
#include <keyboard.h>
#include <arch/x86_64/cpu.h>
#include <stdio.h>

//TODO: Refactor this めちゃくちゃ to use a linked list or something

keyboardState_t state;

uint8_t getKeyboardModifiers() {
    uint8_t modifiers = 0;

    if (state.shiftPressed) {
        modifiers |= KeyboardShift;
    }
    if (state.altPressed) {
        modifiers |= KeyboardAlt;
    }
    if (state.ctrlPressed) {
        modifiers |= KeyboardCtrl;
    }
    if (state.superPressed) {
        modifiers |= KeyboardSuper;
    }

    return modifiers;
}

void ps2KeyboardHandler() {
    uint8_t scancode = inb(0x60);

    switch (scancode) {
        case 0x02:
            keyboardPushKey(D1, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x03:
            keyboardPushKey(D2, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x04:
            keyboardPushKey(D3, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x05:
            keyboardPushKey(D4, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x06:
            keyboardPushKey(D5, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x07:
            keyboardPushKey(D6, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x08:
            keyboardPushKey(D7, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x09:
            keyboardPushKey(D8, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x0A:
            keyboardPushKey(D9, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x0B:
            keyboardPushKey(D0, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x0C:
            keyboardPushKey(Minus, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x0D:
            keyboardPushKey(Equals, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x0E:
            keyboardPushKey(Backspace, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x0F:
            keyboardPushKey(Tab, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x10:
            keyboardPushKey(Q, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x11:
            keyboardPushKey(W, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x12:
            keyboardPushKey(E, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x13:
            keyboardPushKey(R, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x14:
            keyboardPushKey(T, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x15:
            keyboardPushKey(Y, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x16:
            keyboardPushKey(U, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x17:
            keyboardPushKey(I, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x18:
            keyboardPushKey(O, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x19:
            keyboardPushKey(P, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x1A:
            keyboardPushKey(OpenBracket, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x1B:
            keyboardPushKey(CloseBracket, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x1C:
            keyboardPushKey(Enter, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x1D:
            keyboardPushKey(LeftControl, getKeyboardModifiers() | KeyPressed);
            state.ctrlPressed = 1;
            break;
        case 0x1E:
            keyboardPushKey(A, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x1F:
            keyboardPushKey(S, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x20:
            keyboardPushKey(D, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x21:
            keyboardPushKey(F, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x22:
            keyboardPushKey(G, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x23:
            keyboardPushKey(H, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x24:
            keyboardPushKey(J, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x25:
            keyboardPushKey(K, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x26:
            keyboardPushKey(L, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x27:
            keyboardPushKey(Semicolon, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x28:
            keyboardPushKey(SingleQuote, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x29:
            keyboardPushKey(BackTick, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x2A:
            keyboardPushKey(LeftShift, getKeyboardModifiers() | KeyPressed);
            state.shiftPressed = 1;
            break;
        case 0x2B:
            keyboardPushKey(Backslash, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x2C:
            keyboardPushKey(Z, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x2D:
            keyboardPushKey(X, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x2E:
            keyboardPushKey(C, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x2F:
            keyboardPushKey(V, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x30:
            keyboardPushKey(B, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x31:
            keyboardPushKey(N, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x32:
            keyboardPushKey(M, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x33:
            keyboardPushKey(Comma, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x34:
            keyboardPushKey(Period, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x35:
            keyboardPushKey(ForwardSlash, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x36:
            keyboardPushKey(RightShift, getKeyboardModifiers() | KeyPressed);
            state.shiftPressed = 1;
            break;
        case 0x37:
            keyboardPushKey(KeypadStar, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x38:
            keyboardPushKey(LeftAlt, getKeyboardModifiers() | KeyPressed);
            state.altPressed = 1;
            break;
        case 0x39:
            keyboardPushKey(Space, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x3A:
            keyboardPushKey(CapsLock, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x3B:
            keyboardPushKey(F1, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x3C:
            keyboardPushKey(F2, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x3D:
            keyboardPushKey(F3, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x3E:
            keyboardPushKey(F4, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x3F:
            keyboardPushKey(F5, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x40:
            keyboardPushKey(F6, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x41:
            keyboardPushKey(F7, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x42:
            keyboardPushKey(F8, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x43:
            keyboardPushKey(F9, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x44:
            keyboardPushKey(F10, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x45:
            keyboardPushKey(NumLock, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x46:
            keyboardPushKey(ScrollLock, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x47:
            keyboardPushKey(Keypad7, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x48:
            keyboardPushKey(Keypad8, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x49:
            keyboardPushKey(Keypad9, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x4A:
            keyboardPushKey(KeypadMinus, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x4B:
            keyboardPushKey(Keypad4, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x4C:
            keyboardPushKey(Keypad5, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x4D:
            keyboardPushKey(Keypad6, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x4E:
            keyboardPushKey(KeypadPlus, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x4F:
            keyboardPushKey(Keypad1, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x50:
            keyboardPushKey(Keypad2, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x51:
            keyboardPushKey(Keypad3, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x52:
            keyboardPushKey(Keypad0, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x53:
            keyboardPushKey(KeypadDot, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x57:
            keyboardPushKey(F11, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x58:
            keyboardPushKey(F12, getKeyboardModifiers() | KeyPressed);
            break;
        case 0x82:
            keyboardPushKey(D1, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x83:
            keyboardPushKey(D2, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x84:
            keyboardPushKey(D3, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x85:
            keyboardPushKey(D4, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x86:
            keyboardPushKey(D5, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x87:
            keyboardPushKey(D6, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x88:
            keyboardPushKey(D7, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x89:
            keyboardPushKey(D8, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x8A:
            keyboardPushKey(D9, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x8B:
            keyboardPushKey(D0, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x8C:
            keyboardPushKey(Minus, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x8D:
            keyboardPushKey(Equals, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x8E:
            keyboardPushKey(Backspace, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x8F:
            keyboardPushKey(Tab, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x90:
            keyboardPushKey(Q, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x91:
            keyboardPushKey(W, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x92:
            keyboardPushKey(E, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x93:
            keyboardPushKey(R, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x94:
            keyboardPushKey(T, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x95:
            keyboardPushKey(Y, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x96:
            keyboardPushKey(U, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x97:
            keyboardPushKey(I, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x98:
            keyboardPushKey(O, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x99:
            keyboardPushKey(P, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x9A:
            keyboardPushKey(OpenBracket, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x9B:
            keyboardPushKey(CloseBracket, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x9C:
            keyboardPushKey(Enter, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x9D:
            keyboardPushKey(LeftControl, getKeyboardModifiers() | KeyReleased);
            state.ctrlPressed = 0;
            break;
        case 0x9E:
            keyboardPushKey(A, getKeyboardModifiers() | KeyReleased);
            break;
        case 0x9F:
            keyboardPushKey(S, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA0:
            keyboardPushKey(D, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA1:
            keyboardPushKey(F, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA2:
            keyboardPushKey(G, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA3:
            keyboardPushKey(H, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA4:
            keyboardPushKey(J, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA5:
            keyboardPushKey(K, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA6:
            keyboardPushKey(L, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA7:
            keyboardPushKey(Semicolon, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA8:
            keyboardPushKey(SingleQuote, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xA9:
            keyboardPushKey(BackTick, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xAA:
            keyboardPushKey(LeftShift, getKeyboardModifiers() | KeyReleased);
            state.shiftPressed = 0;
            break;
        case 0xAB:
            keyboardPushKey(Backslash, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xAC:
            keyboardPushKey(Z, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xAD:
            keyboardPushKey(X, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xAE:
            keyboardPushKey(C, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xAF:
            keyboardPushKey(V, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xB0:
            keyboardPushKey(B, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xB1:
            keyboardPushKey(N, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xB2:
            keyboardPushKey(M, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xB3:
            keyboardPushKey(Comma, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xB4:
            keyboardPushKey(Period, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xB5:
            keyboardPushKey(ForwardSlash, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xB6:
            keyboardPushKey(RightShift, getKeyboardModifiers() | KeyReleased);
            state.shiftPressed = 0;
            break;
        case 0xB7:
            keyboardPushKey(KeypadStar, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xB8:
            keyboardPushKey(LeftAlt, getKeyboardModifiers() | KeyReleased);
            state.altPressed = 0;
            break;
        case 0xB9:
            keyboardPushKey(Space, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xBA:
            keyboardPushKey(CapsLock, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xBB:
            keyboardPushKey(F1, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xBC:
            keyboardPushKey(F2, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xBD:
            keyboardPushKey(F3, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xBE:
            keyboardPushKey(F4, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xBF:
            keyboardPushKey(F5, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC0:
            keyboardPushKey(F6, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC1:
            keyboardPushKey(F7, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC2:
            keyboardPushKey(F8, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC3:
            keyboardPushKey(F9, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC4:
            keyboardPushKey(F10, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC5:
            keyboardPushKey(NumLock, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC6:
            keyboardPushKey(ScrollLock, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC7:
            keyboardPushKey(Keypad7, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC8:
            keyboardPushKey(Keypad8, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xC9:
            keyboardPushKey(Keypad9, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xCA:
            keyboardPushKey(KeypadMinus, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xCB:
            keyboardPushKey(Keypad4, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xCC:
            keyboardPushKey(Keypad5, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xCD:
            keyboardPushKey(Keypad6, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xCE:
            keyboardPushKey(KeypadPlus, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xCF:
            keyboardPushKey(Keypad1, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xD0:
            keyboardPushKey(Keypad2, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xD1:
            keyboardPushKey(Keypad3, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xD2:
            keyboardPushKey(Keypad0, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xD3:
            keyboardPushKey(KeypadDot, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xD7:
            keyboardPushKey(F11, getKeyboardModifiers() | KeyReleased);
            break;
        case 0xD8:
            keyboardPushKey(F12, getKeyboardModifiers() | KeyReleased);
            break;
        default:
            // Handle other keys or ignore
            break;
    }
}