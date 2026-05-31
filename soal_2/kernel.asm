bits 16

global _start
global _putInMemory
global _getChar
extern _main

_start:

    cli

    mov ax, cs
    mov ds, ax
    mov es, ax

    sti

    call _main

.hang:
    jmp .hang


_putInMemory:
    push bp
    mov bp, sp

    push ds

    mov ax, [bp+4]
    mov si, [bp+6]
    mov cl, [bp+8]

    mov ds, ax
    mov [si], cl

    pop ds

    pop bp
    ret

; implement this
_getChar:
    ; YOUR CODE
	_getChar:
    mov ah, 0       ; Menyiapkan instruksi BIOS untuk menunggu tombol ditekan
    int 0x16        ; Memanggil interupsi keyboard (Interrupt 16h)
    ret             ; Kembali ke program C dengan membawa kode karakter di register AL
