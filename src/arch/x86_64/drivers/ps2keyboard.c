#include <stdint.h>
#include <arch/x86_64/drivers/ps2keyboard.h>
#include <arch/x86_64/cpu.h>
#include <stdio.h>

//TODO: Refactor this Bullshit to use a linked list or something and also for the love of god use a keypress packet

char keyboardBuffer[256];
int bufferIndex = 0;

keyboardState_t state;

void bufferPushChar(char c) {
    if (bufferIndex < sizeof(keyboardBuffer) - 1) {
        keyboardBuffer[bufferIndex] = c;
        bufferIndex++;
        keyboardBuffer[bufferIndex] = '\0'; // Null-terminate the string
    }
}

void bufferRemoveChar() {
    if (bufferIndex > 0) {
        bufferIndex--;
        keyboardBuffer[bufferIndex] = '\0'; // Null-terminate the string
    }
}

void ps2KeyboardHandler() {
    uint8_t scancode = inb(0x60);

    switch (scancode) {
        case 0x02:
            if (state.shiftPressed) {
                bufferPushChar('!');
            }
            else {
                bufferPushChar('1');
            }
            break;
        case 0x03:
            if (state.shiftPressed) {
                bufferPushChar('@');
            }
            else {
                bufferPushChar('2');
            }
            break;
        case 0x04:
            if (state.shiftPressed) {
                bufferPushChar('#');
            }
            else {
                bufferPushChar('3');
            }
            break;
        case 0x05:
            if (state.shiftPressed) {
                bufferPushChar('$');
            }
            else {
                bufferPushChar('4');
            }
            break;
        case 0x06:
            if (state.shiftPressed) {
            bufferPushChar('%');
            }
            else {
            bufferPushChar('5');
            }
            break;
        case 0x07:
            if (state.shiftPressed) {
            bufferPushChar('^');
            }
            else {
            bufferPushChar('6');
            }
            break;
        case 0x08:
            if (state.shiftPressed) {
            bufferPushChar('&');
            }
            else {
            bufferPushChar('7');
            }
            break;
        case 0x09:
            if (state.shiftPressed) {
            bufferPushChar('*');
            }
            else {
            bufferPushChar('8');
            }
            break;
        case 0x0A:
            if (state.shiftPressed) {
            bufferPushChar('(');
            }
            else {
            bufferPushChar('9');
            }
            break;
        case 0x0B:
            if (state.shiftPressed) {
            bufferPushChar(')');
            }
            else {
            bufferPushChar('0');
            }
            break;
        case 0x0C:
            if (state.shiftPressed) {
            bufferPushChar('_');
            }
            else {
            bufferPushChar('-');
            }
            break;
        case 0x0D:
            if (state.shiftPressed) {
            bufferPushChar('+');
            }
            else {
            bufferPushChar('=');
            }
            break;
        case 0x0E:
            bufferRemoveChar(); // Backspace
            break;
        case 0x0F:
            bufferPushChar('\t'); // Tab
            break;
        case 0x10:
            if (state.shiftPressed) {
                bufferPushChar('Q');
            }
            else {
                bufferPushChar('q');
            }
            break;
        case 0x11:
            if (state.shiftPressed) {
                bufferPushChar('W');
            }
            else {
                bufferPushChar('w');
            }
            break;
        case 0x12:
            if (state.shiftPressed) {
                bufferPushChar('E');
            }
            else {
                bufferPushChar('e');
            }
            break;
        case 0x13:
            if (state.shiftPressed) {
                bufferPushChar('R');
            }
            else {
                bufferPushChar('r');
            }
            break;
        case 0x14:
            if (state.shiftPressed) {
            bufferPushChar('T');
            }
            else {
            bufferPushChar('t');
            }
            break;
        case 0x15:
            if (state.shiftPressed) {
            bufferPushChar('Y');
            }
            else {
            bufferPushChar('y');
            }
            break;
        case 0x16:
            if (state.shiftPressed) {
            bufferPushChar('U');
            }
            else {
            bufferPushChar('u');
            }
            break;
        case 0x17:
            if (state.shiftPressed) {
            bufferPushChar('I');
            }
            else {
            bufferPushChar('i');
            }
            break;
        case 0x18:
            if (state.shiftPressed) {
            bufferPushChar('O');
            }
            else {
            bufferPushChar('o');
            }
            break;
        case 0x19:
            if (state.shiftPressed) {
            bufferPushChar('P');
            }
            else {
            bufferPushChar('p');
            }
            break;
        case 0x1A:
            if (state.shiftPressed) {
            bufferPushChar('{');
            }
            else {
            bufferPushChar('[');
            }
            break;
        case 0x1B:
            if (state.shiftPressed) {
            bufferPushChar('}');
            }
            else {
            bufferPushChar(']');
            }
            break;
        case 0x1C:
            bufferPushChar('\n'); // Enter
            break;
        default:
            // Handle other keys or ignore
            break;
    }
}

void readLine(char *buffer) {
    while (bufferIndex == 0 || keyboardBuffer[bufferIndex - 1] != '\n') {
        // Wait for a newline character
    }
    for (int i = 0; i < bufferIndex; i++) {
        buffer[i] = keyboardBuffer[i];
    }
    buffer[bufferIndex - 1] = '\0'; // Remove the newline character
    bufferIndex = 0;
    keyboardBuffer[bufferIndex] = '\0'; // 'Clear' the buffer
}

char readKey() {
    while (bufferIndex == 0) {
        // Wait for a key to be pressed
    }
    char c = keyboardBuffer[0];
    bufferRemoveChar();
    return c;
}