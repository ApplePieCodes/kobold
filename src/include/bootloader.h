// The Kobold Kernel

// src/include/bootloader.h
// April 2025

// Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
// This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <limine.h>

extern volatile struct limine_framebuffer_request framebuffer_request;

extern volatile struct limine_memmap_request memmap_request;

extern volatile struct limine_hhdm_request hhdm_request;

#endif