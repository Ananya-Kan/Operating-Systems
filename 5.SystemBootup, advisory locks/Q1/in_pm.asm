[bits 16]
switch:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    xor eax, 0x0001
    mov cr0, eax
    jmp CODE:in_pm



[bits 32]

in_pm:
    mov ax, DATA
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x9000
    mov esp, ebp         

    call print_hw           
           
    mov edx, 32
    mov ecx, cr0
    mov ebx, 000B8010h
    add ebx, 1330      
    loop:
        mov eax, 00000130h 
        shl ecx, 1         
        adc eax, 0
        mov [ebx], ax      
        add ebx, 2         
        dec edx            
        jnz loop

    jmp $

print_hw:
    pusha                   
    mov ebx, HELLO        
    mov edx, 000B8000h      
    add edx, 1300           
    loops:
        mov al, [ebx]
        add ebx, 1       
        cmp al, 0           
        je pm_return        
        mov [edx], al          
        add edx, 2           
        jmp loops           

pm_return:
    popa
    ret                          

HELLO: db "Hello world", 0
