default: compile run


compile: 
	nasm -f bin boot.asm -o boot

run: compile
	qemu-system-x86_64 boot