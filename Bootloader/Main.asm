[org 0x7c00]
KernelLocation equ 0x1000

    mov [BootDrive], dl
    mov bp, 0x9000
    mov sp, bp

    mov bx, TextKernelMessage
    call PrintString

    mov bx, GraphicsKernelMessage
    call PrintString

    je WaitFor

    WaitFor:
        mov ah, 0x0
        int 0x16
        cmp al, '1'
        je LoadTextKernel
        cmp al, '2'
        je Load13HKernel
        jmp WaitFor

    LoadTextKernel:
        call LoadKernelTextMode
        call SwitchProtectedMode

        jmp $

    Load13HKernel:
        call LoadKernel13H
        call SwitchProtectedMode

        jmp $

%include "Bootloader/PrintString.asm"
%include "Bootloader/DiskLoad.asm"
%include "Bootloader/Gdt.asm"
%include "Bootloader/SwitchProtectedMode.asm"

[bits 16]
LoadKernelTextMode:
    mov bx, KernelLocation
    mov dh, 54
    mov dl, [BootDrive]
    call DiskLoad

    ; mov ax, 0x4f02
    ; mov bx, 0x104
    ; int 0x10

    ret

LoadKernel13H:
    mov bx, KernelLocation
    mov dh, 54
    mov dl, [BootDrive]
    call DiskLoad

    mov ah, 0x00
    mov al, 0x13
    int 0x10

    ret

[bits 32]
BeginProtectedMode:
    call KernelLocation
    jmp $

BootDrive db 0
TextKernelMessage db "Press 1 key to load textmode kernel.", 13, 10, 0
GraphicsKernelMessage db "Press 2 key to load 13h kernel. (Need to install GUI)", 13, 10, 0

times 510 - ($-$$) db 0
dw 0xaa55