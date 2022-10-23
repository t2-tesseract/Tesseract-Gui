extern IsrIrqHandler

IrqHandler:
    pusha                 ; push all registers
    mov ax, ds
    push eax              ; save ds

    mov ax, 0x10          ; load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call IsrIrqHandler
    pop esp

    pop ebx                ; restore kernel data segment
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                ; restore all registers
    add esp, 0x8        ; restore stack for erro no been pushed

    sti                 ; re-enable interrupts
    iret


%macro Irq 2
  global Irq%1
  Irq%1:
    cli
    push byte 0
    push byte %2
    jmp IrqHandler
%endmacro


Irq 0, 32
Irq 1, 33
Irq 2, 34
Irq 3, 35
Irq 4, 36
Irq 5, 37
Irq 6, 38
Irq 7, 39
Irq 8, 40
Irq 9, 41
Irq 10, 42
Irq 11, 43
Irq 12, 44
Irq 13, 45
Irq 14, 46
Irq 15, 47

extern IsrExceptionHandler
global Exception0
global Exception1
global Exception2
global Exception3
global Exception4
global Exception5
global Exception6
global Exception7
global Exception8
global Exception9
global Exception10
global Exception11
global Exception12
global Exception13
global Exception14
global Exception15
global Exception16
global Exception17
global Exception18
global Exception19
global Exception20
global Exception21
global Exception22
global Exception23
global Exception24
global Exception25
global Exception26
global Exception27
global Exception28
global Exception29
global Exception30
global Exception31
global Exception128


ExceptionHandler:
    pusha                 ; push all registers
    mov ax, ds
    push eax              ; save ds
    
    mov ax, 0x10          ; load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call IsrExceptionHandler

    pop ebx             ; restore kernel data segment
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                ; restore all registers
    add esp, 0x8        ; restore stack for erro no been pushed

    sti                 ; re-enable interrupts
    iret


Exception0:
    cli
    push byte 0     ; store default err code(0)
    push 0          ; push exception number index in IDT
    jmp ExceptionHandler
    pusha
    popa

Exception1:
    cli
    push byte 0     ; store default err code(0)
    push 1          ; push exception number index in IDT
    jmp ExceptionHandler


Exception2:
    cli
    push byte 0     ; store default err code(0)
    push 2          ; push exception number index in IDT
    jmp ExceptionHandler


Exception3:
    cli
    push byte 0     ; store default err code(0)
    push 3          ; push exception number index in IDT
    jmp ExceptionHandler


Exception4:
    cli
    push byte 0     ; store default err code(0)
    push 4          ; push exception number index in IDT
    jmp ExceptionHandler


Exception5:
    cli
    push byte 0     ; store default err code(0)
    push 5          ; push exception number index in IDT
    jmp ExceptionHandler


Exception6:
    cli
    push byte 0     ; store default err code(0)
    push 6          ; push exception number index in IDT
    jmp ExceptionHandler


Exception7:
    cli
    push byte 0     ; store default err code(0)
    push 7          ; push exception number index in IDT
    jmp ExceptionHandler


Exception8:
    cli
    push 8          ; push exception number index in IDT
    jmp ExceptionHandler


Exception9:
    cli
    push byte 0     ; store default err code(0)
    push 9          ; push exception number index in IDT
    jmp ExceptionHandler


Exception10:
    cli
    push 10          ; push exception number index in IDT
    jmp ExceptionHandler


Exception11:
    cli
    push 11          ; push exception number index in IDT
    jmp ExceptionHandler


Exception12:
    cli
    push 12          ; push exception number index in IDT
    jmp ExceptionHandler


Exception13:
    cli
    push 13          ; push exception number index in IDT
    jmp ExceptionHandler


Exception14:
    cli
    push 14          ; push exception number index in IDT
    jmp ExceptionHandler


Exception15:
    cli
    push byte 0     ; store default err code(0)
    push 15          ; push exception number index in IDT
    jmp ExceptionHandler


Exception16:
    cli
    push byte 0     ; store default err code(0)
    push 16          ; push exception number index in IDT
    jmp ExceptionHandler


Exception17:
    cli
    push byte 0     ; store default err code(0)
    push 17          ; push exception number index in IDT
    jmp ExceptionHandler


Exception18:
    cli
    push byte 0     ; store default err code(0)
    push 18          ; push exception number index in IDT
    jmp ExceptionHandler


Exception19:
    cli
    push byte 0     ; store default err code(0)
    push 19          ; push exception number index in IDT
    jmp ExceptionHandler


Exception20:
    cli
    push byte 0     ; store default err code(0)
    push 20          ; push exception number index in IDT
    jmp ExceptionHandler


Exception21:
    cli
    push byte 0     ; store default err code(0)
    push 21          ; push exception number index in IDT
    jmp ExceptionHandler


Exception22:
    cli
    push byte 0     ; store default err code(0)
    push 22          ; push exception number index in IDT
    jmp ExceptionHandler


Exception23:
    cli
    push byte 0     ; store default err code(0)
    push 23          ; push exception number index in IDT
    jmp ExceptionHandler


Exception24:
    cli
    push byte 0     ; store default err code(0)
    push 24          ; push exception number index in IDT
    jmp ExceptionHandler


Exception25:
    cli
    push byte 0     ; store default err code(0)
    push 25          ; push exception number index in IDT
    jmp ExceptionHandler


Exception26:
    cli
    push byte 0     ; store default err code(0)
    push 26          ; push exception number index in IDT
    jmp ExceptionHandler


Exception27:
    cli
    push byte 0     ; store default err code(0)
    push 27          ; push exception number index in IDT
    jmp ExceptionHandler


Exception28:
    cli
    push byte 0     ; store default err code(0)
    push 28          ; push exception number index in IDT
    jmp ExceptionHandler


Exception29:
    cli
    push byte 0     ; store default err code(0)
    push 29          ; push exception number index in IDT
    jmp ExceptionHandler


Exception30:
    cli
    push byte 0     ; store default err code(0)
    push 30          ; push exception number index in IDT
    jmp ExceptionHandler


Exception31:
    cli
    push byte 0     ; store default err code(0)
    push 31          ; push exception number index in IDT
    jmp ExceptionHandler


Exception128:
    cli
    push byte 0     ; store default err code(0)
    push 128          ; push exception number index in IDT
    jmp ExceptionHandler


