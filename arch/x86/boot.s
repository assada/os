.set ALIGN,    1<<0             
.set MEMINFO,  1<<1             
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002       
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
.global stack_bottom
.global stack_top
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp
    
    pushl $0
    popf
    
    pushl %ebx
    
    call kernel_main

    cli
1:  hlt
    jmp 1b

.size _start, . - _start