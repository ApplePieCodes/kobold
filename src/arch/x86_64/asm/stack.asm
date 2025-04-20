[bits 64]
extern initStage2

global stage2Forwarder
stage2Forwarder: ; Creates a bigger stack and jumps to stage 2
    mov rsp, rdi
    call initStage2