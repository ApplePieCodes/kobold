// The Kobold Kernel

// src/term/term.c

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

#include <limine.h>
#include <spinlock.h>
#include <bootloader.h>
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include <stdio.h>
#include <colors.h>
#include <term/term.h>
#include <stddef.h>

struct flanterm_context *context;
spinlock_t termLock;

void initTerm() {
    spinlockLock(&termLock);

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    context = flanterm_fb_init(
        NULL,
        NULL,
        framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch,
        framebuffer->red_mask_size, framebuffer->red_mask_shift,
        framebuffer->green_mask_size, framebuffer->green_mask_shift,
        framebuffer->blue_mask_size, framebuffer->blue_mask_shift,
        NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, 0, 0, 1,
        2, 2,
        0
    );

    spinlockUnlock(&termLock);
	printf("[" BGRN "TERMINAL" WHT "] Terminal Initialized\n");
}

void getScreenSize(size_t *columns, size_t *rows) {
    return flanterm_get_dimensions(context, columns, rows);
}

void clearScreen() {
    printf(BLKB "\033[2J");
    printf("\x1b[H");
}

int termWriteChar(char c) {
    spinlockLock(&termLock);
    flanterm_write(context, &c, 1);
    spinlockUnlock(&termLock);

    return 1;
}