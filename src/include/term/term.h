// The Kobold Kernel

// src/include/term/term.h
// April 2025

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

#include <stddef.h>

#ifndef TERM_H
#define TERM_H

void initTerm();
void clearScreen();
int termWriteChar(char c);
void getScreenSize(size_t *columns, size_t *rows);
void clearScreen();

#endif