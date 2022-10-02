extern CDefaultInt, ClockInt, KeyboardInt, MainMenuKeys
global DefaultInt, Irq0, Irq1, MainMenuAsm

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

MainMenuAsm:
        call MainMenuKeys
        mov al, 0x20
        out 0x20, al
        iret