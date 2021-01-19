[bits 16]
[org 0x7c00]

mov bp, 0x9000
mov sp, bp
xor ax, ax              
mov es, ax              
mov ds, ax
mov ss, ax

%include "in_pm.asm"
%include "gdt.asm"

[bits 32]

call switch

times 510-($-$$) db 0
dw 0xaa55
