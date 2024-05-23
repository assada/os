.section .text
.align 4

.global gdt_flush
.type gdt_flush, @function
gdt_flush:
   lgdt gdt_ptr
   jmp $0x08, $reload_cs

   reload_cs:
      movw $0x10, %ax
      movw %ax, %ds
      movw %ax, %es
      movw %ax, %fs
      movw %ax, %gs
      movw %ax, %ss
      ret
