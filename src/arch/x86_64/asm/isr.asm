[bits 64]

%macro pushaq 0
    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popaq 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax
%endmacro

%macro isr_stub 1
	global isr_%1
    isr_%1:
        push 0
        push %1
        jmp isr_common_handler
%endmacro

%macro isr_stub_err 1
	global isr_%1
    isr_%1:
        push %1
        jmp isr_common_handler
%endmacro

isr_stub 0
isr_stub 1
isr_stub 2
isr_stub 3
isr_stub 4
isr_stub 5
isr_stub 6
isr_stub 7
isr_stub_err 8
isr_stub 9
isr_stub_err 10
isr_stub_err 11
isr_stub_err 12
isr_stub_err 13
isr_stub_err 14
isr_stub 15
isr_stub 16
isr_stub_err 17
isr_stub 18
isr_stub 19
isr_stub 20
isr_stub_err 21
isr_stub 22
isr_stub 23
isr_stub 24
isr_stub 25
isr_stub 26
isr_stub 27
isr_stub 28
isr_stub_err 29
isr_stub_err 30
isr_stub 31

extern isr_common_handler_c

isr_common_handler:
    cli
    pushaq

    mov rax, cr0
	push rax
	mov rax, cr2
	push rax
	mov rax, cr3
	push rax
	mov rax, cr4
	push rax

    mov rdi, rsp

    call isr_common_handler_c

    pop rax
	pop rax
	pop rax
	pop rax
	popaq

	add rsp, 16

	sti
	iretq