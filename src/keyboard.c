#include <keyboard.h>
#include <stdio.h>

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

void readLine(char *buffer) {
    uint64_t bufferIndex = 0;
    
    while (1) {
        keypress_t k = keyboardReadKey();

        switch (k.key) {
            case D1:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '!';
                        printf("!");
                    }
                    else {
                        buffer[bufferIndex++] = '1';
                        printf("1");
                    }
                }
                break;
            case D2:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '@';
                        printf("@");
                    }
                    else {
                        buffer[bufferIndex++] = '2';
                        printf("2");
                    }
                }
                break;
            case D3:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '#';
                        printf("#");
                    }
                    else {
                        buffer[bufferIndex++] = '3';
                        printf("3");
                    }
                }
                break;
            case D4:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '$';
                        printf("$");
                    }
                    else {
                        buffer[bufferIndex++] = '4';
                        printf("4");
                    }
                }
                break;
            case D5:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '%';
                        printf("%");
                    }
                    else {
                        buffer[bufferIndex++] = '5';
                        printf("5");
                    }
                }
                break;
            case D6:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '^';
                        printf("^");
                    }
                    else {
                        buffer[bufferIndex++] = '6';
                        printf("6");
                    }
                }
                break;
            case D7:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '&';
                        printf("&");
                    }
                    else {
                        buffer[bufferIndex++] = '7';
                        printf("7");
                    }
                }
                break;
            case D8:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '*';
                        printf("*");
                    }
                    else {
                        buffer[bufferIndex++] = '8';
                        printf("8");
                    }
                }
                break;
            case D9:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '(';
                        printf("(");
                    }
                    else {
                        buffer[bufferIndex++] = '9';
                        printf("9");
                    }
                }
                break;
            case D0:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = ')';
                        printf(")");
                    }
                    else {
                        buffer[bufferIndex++] = '0';
                        printf("0");
                    }
                }
                break;
            case Minus:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '_';
                        printf("_");
                    }
                    else {
                        buffer[bufferIndex++] = '-';
                        printf("-");
                    }
                }
                break;
            case Equals:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '+';
                        printf("+");
                    }
                    else {
                        buffer[bufferIndex++] = '=';
                        printf("=");
                    }
                }
                break;
            case Backspace:
                if (k.modifiers & KeyPressed) {
                    if (bufferIndex > 0) {
                        bufferIndex -= 1;
                        if (buffer[bufferIndex] == '\t') {
                            printf("\b\b\b\b\b\b\b\b \b"); // Should work?
                        }
                        else {
                            printf("\b \b");
                        }
                    }
                }
                break;
            case Tab:
                if (k.modifiers & KeyPressed) {
                    buffer[bufferIndex++] = '\t';
                    printf("\t");
                }
                break;
            case Q:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'Q';
                        printf("Q");
                    }
                    else {
                        buffer[bufferIndex++] = 'q';
                        printf("q");
                    }
                }
                break;
            case W:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'W';
                        printf("W");
                    }
                    else {
                        buffer[bufferIndex++] = 'w';
                        printf("w");
                    }
                }
                break;
            case E:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'E';
                        printf("E");
                    }
                    else {
                        buffer[bufferIndex++] = 'e';
                        printf("e");
                    }
                }
                break;
            case R:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'R';
                        printf("R");
                    }
                    else {
                        buffer[bufferIndex++] = 'r';
                        printf("r");
                    }
                }
                break;
            case T:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'T';
                        printf("T");
                    }
                    else {
                        buffer[bufferIndex++] = 't';
                        printf("t");
                    }
                }
                break;
            case Y:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'Y';
                        printf("Y");
                    }
                    else {
                        buffer[bufferIndex++] = 'y';
                        printf("y");
                    }
                }
                break;
            case U:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'U';
                        printf("U");
                    }
                    else {
                        buffer[bufferIndex++] = 'u';
                        printf("u");
                    }
                }
                break;
            case I:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'I';
                        printf("I");
                    }
                    else {
                        buffer[bufferIndex++] = 'i';
                        printf("i");
                    }
                }
                break;
            case O:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'O';
                        printf("O");
                    }
                    else {
                        buffer[bufferIndex++] = 'o';
                        printf("o");
                    }
                }
                break;
            case P:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'P';
                        printf("P");
                    }
                    else {
                        buffer[bufferIndex++] = 'p';
                        printf("p");
                    }
                }
                break;
            case OpenBracket:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '{';
                        printf("{");
                    }
                    else {
                        buffer[bufferIndex++] = '[';
                        printf("[");
                    }
                }
                break;
            case CloseBracket:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '}';
                        printf("}");
                    }
                    else {
                        buffer[bufferIndex++] = ']';
                        printf("]");
                    }
                }
                break;
            case Enter:
                if (k.modifiers & KeyPressed) {
                    printf("\n");
                    buffer[bufferIndex] = '\0';
                    return;
                }
                break;
            case A:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'A';
                        printf("A");
                    }
                    else {
                        buffer[bufferIndex++] = 'a';
                        printf("a");
                    }
                }
                break;
            case S:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'S';
                        printf("S");
                    }
                    else {
                        buffer[bufferIndex++] = 's';
                        printf("s");
                    }
                }
                break;
            case D:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'D';
                        printf("D");
                    }
                    else {
                        buffer[bufferIndex++] = 'd';
                        printf("d");
                    }
                }
                break;
            case F:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'F';
                        printf("F");
                    }
                    else {
                        buffer[bufferIndex++] = 'f';
                        printf("f");
                    }
                }
                break;
            case G:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'G';
                        printf("G");
                    }
                    else {
                        buffer[bufferIndex++] = 'g';
                        printf("g");
                    }
                }
                break;
            case H:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'H';
                        printf("H");
                    }
                    else {
                        buffer[bufferIndex++] = 'h';
                        printf("h");
                    }
                }
                break;
            case J:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'J';
                        printf("J");
                    }
                    else {
                        buffer[bufferIndex++] = 'j';
                        printf("j");
                    }
                }
                break;
            case K:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'K';
                        printf("K");
                    }
                    else {
                        buffer[bufferIndex++] = 'k';
                        printf("k");
                    }
                }
                break;
            case L:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'L';
                        printf("L");
                    }
                    else {
                        buffer[bufferIndex++] = 'l';
                        printf("l");
                    }
                }
                break;
            case Semicolon:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = ':';
                        printf(":");
                    }
                    else {
                        buffer[bufferIndex++] = ';';
                        printf(";");
                    }
                }
                break;
            case SingleQuote:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '"';
                        printf("\"");
                    }
                    else {
                        buffer[bufferIndex++] = '\'';
                        printf("'");
                    }
                }
                break;
            case BackTick:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '~';
                        printf("~");
                    }
                    else {
                        buffer[bufferIndex++] = '`';
                        printf("`");
                    }
                }
                break;
            case Backslash:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '|';
                        printf("|");
                    }
                    else {
                        buffer[bufferIndex++] = '\\';
                        printf("\\");
                    }
                }
                break;
            case Z:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'Z';
                        printf("Z");
                    }
                    else {
                        buffer[bufferIndex++] = 'z';
                        printf("z");
                    }
                }
                break;
            case X:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'X';
                        printf("X");
                    }
                    else {
                        buffer[bufferIndex++] = 'x';
                        printf("x");
                    }
                }
                break;
            case C:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'C';
                        printf("C");
                    }
                    else {
                        buffer[bufferIndex++] = 'c';
                        printf("c");
                    }
                }
                break;
            case V:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'V';
                        printf("V");
                    }
                    else {
                        buffer[bufferIndex++] = 'v';
                        printf("v");
                    }
                }
                break;
            case B:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'B';
                        printf("B");
                    }
                    else {
                        buffer[bufferIndex++] = 'b';
                        printf("b");
                    }
                }
                break;
            case N:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'N';
                        printf("N");
                    }
                    else {
                        buffer[bufferIndex++] = 'n';
                        printf("n");
                    }
                }
                break;
            case M:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = 'M';
                        printf("M");
                    }
                    else {
                        buffer[bufferIndex++] = 'm';
                        printf("m");
                    }
                }
                break;
            case Comma:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '<';
                        printf("<");
                    }
                    else {
                        buffer[bufferIndex++] = ',';
                        printf(",");
                    }
                }
                break;
            case Period:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '>';
                        printf(">");
                    }
                    else {
                        buffer[bufferIndex++] = '.';
                        printf(".");
                    }
                }
                break;
            case ForwardSlash:
                if (k.modifiers & KeyPressed) {
                    if (k.modifiers & KeyboardShift) {
                        buffer[bufferIndex++] = '?';
                        printf("?");
                    }
                    else {
                        buffer[bufferIndex++] = '/';
                        printf("/");
                    }
                }
                break;
            case Space:
                if (k.modifiers & KeyPressed) {
                    buffer[bufferIndex++] = ' ';
                    printf(" ");
                }
                break;
            default:
                // Ignore other keys
                break;
        }
    }
}