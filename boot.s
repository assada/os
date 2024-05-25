.set ALIGN,    1<<0             
.set MEMINFO,  1<<1             
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002       /* multiboot 1 */
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .stack, "aw", @nobits
.global stack_top
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
   movl $stack_top, %esp

   push %ebx

   call kernel_main
1:
   jmp 1b
