extern CDefaultInt, ClockInt, KeyboardInt, MouseInt
global DefaultInt, Irq0, Irq1, Irq12

DefaultInt:
	call CDefaultInt
	mov al, 0x20
	out 0x20, al
	iret

Irq0:
        call ClockInt
        mov al, 0x20
        out 0x20, al
        iret

Irq1:
        call KeyboardInt
        mov al, 0x20
        out 0x20, al
        iret

Irq12:
        call MouseInt
        mov al, 0x20
        out 0x20, al
        iret