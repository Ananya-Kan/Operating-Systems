[bits 16]

gdt_start:
    gdt_null:
        dd 00000000000000000000000000000000b, 00000000000000000000000000000000b
    gdt_code:
        dw 1111111111111111b, 0000000000000000b
        db 00000000b, 10011010b, 11001111b, 00000000b
    gdt_data:
        dw 1111111111111111b, 0000000000000000b
        db 00000000b, 10010010b, 11001111b, 00000000b
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE equ gdt_code - gdt_start
DATA equ gdt_data - gdt_start