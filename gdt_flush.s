.global gdt_flush

gdt_flush:
   lgdt gdtp
   jmp $0x08, $reload_cs

   reload_cs:
      movw $0x10, %ax
      movw %ax, %ds
      movw %ax, %es
      movw %ax, %fs
      movw %ax, %gs
      movw %ax, %ss
      ret
