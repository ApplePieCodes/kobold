project('kobold', 'c', 'nasm',
    version : '0.0.1',
    default_options : ['optimization=plain'])

kernel_sources = files(
    'src/arch/x86_64/init.c',

    'src/term/flanterm/flanterm.c',
    'src/term/flanterm/backends/fb.c',
    'src/term/term.c',

    'src/bootloader.c',

    'src/arch/x86_64/gdt.c',
    'src/arch/x86_64/asm/gdt.asm',

    'src/arch/x86_64/pmm.c',
    'src/arch/x86_64/vmm.c',
    
    'src/arch/x86_64/idt.c',
    'src/arch/x86_64/pic.c',
    'src/arch/x86_64/asm/isr.asm',


    'src/libc/abort.c',
    'src/libc/stdio/printf.c',
    'src/libc/stdio/putchar.c',
    'src/libc/stdio/puts.c',
    'src/libc/string/memcmp.c',
    'src/libc/string/memcpy.c',
    'src/libc/string/memmove.c',
    'src/libc/string/memset.c',
    'src/libc/string/strlen.c',
)

add_global_arguments('-ffreestanding', '-std=gnu11', '-Wall', '-Wextra', '-mcmodel=kernel', '-g', '-mgeneral-regs-only', '-mno-red-zone', '-mno-sse', '-mno-sse2', '-mno-mmx', '-fno-omit-frame-pointer', '-mno-80387', language: 'c')

kernel_exe = executable('kobold', 
    kernel_sources,
    install : false,
    link_args : ['-nostdlib', '-T', '../res/linker/linker-x86_64.ld'],
    include_directories: ['src/include', 'src/include/libc']
)