PrintString:
    pusha
    mov ah, 0x0e

Loop:
    mov al, [bx]
    int 0x10
    add bx, 1
    mov al, [bx]
    cmp al, 0
    jne Loop
    popa 
    ret