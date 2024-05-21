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

.section .bss
.align 16

stack_bottom:
	.skip 1024 * 32  # 32 KB

stack_top:
	.section .text
	.global _start
	.type _start, @function
_start:
	cli
	mov $stack_top, %esp

	call	kernel_main

	hlt
	jmp 1
1:
	jmp	1


.size _start, . - _start
