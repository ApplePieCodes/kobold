; The Kobold Kernel

; src/arch/x86_64/asm/gdt.asm

; Liam Greenway (liamgr33nway@gmail.com, @applepieonrye on Discord)
; This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

[bits 64]

global loadCS
loadCS: ; Sets the CS Register.
    pop rdi ; Grab the return Instruction Pointer
    push 0x08 ; Segment Selector
    push rdi ; Pop Return Instruction Pointer
    retfq ; Far Return