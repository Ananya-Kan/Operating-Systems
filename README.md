# Operating-Systems

Various Projects implemented to understand the concepts of the course: operating systems. 
Assignment 2 includes Booting the kernel and implementing our own System Call.

Assignment 5:Implemented a simple bootloader, booted via a legacy BIOS. Program written in assembly language and a bootable binary needs created. This bootable binary should basically represent the boot sector of a disk and should be recognized by the BIOS as a bootable image using qemu emulator. program switches to the protected mode (32-bits) and thereafter prints “Hello world!” and the contents of the CR0 register (the one used to turn on protected mode).
The second exercise deals with **advisory file locks** (e.g. POSIX flock() and the likes). used the C library functions in termios.h for opening and editing files and advisory locks such that two simultaneous accesses to the same file using the editor throw an advisory warning on the one who opens the file that already is advisory locked. However,the access is not blocked. The user who receives the warning is able to edit the file (regardless of race conditions).

Assignment 4:Implemented a modified Dining Philosophers Problem by **designing a counting semaphore structure** using mutex called my semaphore so that multiple pthreads can synchronize access to some limited/shared resource. The counting semaphores use the signalling mechanism the way semaphores work, i.e. signalling a thread that waits on a semaphore and it also implements the primitives wait(), signal() and signal(printValue) for debugging. 
Also implemented non-blocking variants of wait() and signal() using the non-blocking functions available in the Pthreads library.

Assignment 3: **Modifying the CFS Scheduler in Linux.** Added a soft real-time requirement to a process – say something like each process, that requires soft real-time
guarantees must receive atleast x units of time-slice. Every time the scheduler is called, checked if the real-time guarantees of process with soft-
realtime requirements are being met or not. given higher priority to processes with soft-realtime requirement compared to the vruntime that is normally considered.

Assignment 2: a).Studied the difference between forked processes and threads by operations on the value of a global variable.
b).**Created own system call in C**, called sh task info(), which takes argument as PID. It searches out the task struct() corresponding to the PID and prints out all the fields corresponding to it and also saves it in a file. The file name is supplied as an argument to the system call. Downloaded the kernel version 5.9.1 from the official repository of the Linux distribution ,compiled and boot that up to implement the system call.
