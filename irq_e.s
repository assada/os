.section .text
.align 4

.macro IRQ index entry
   .global irq\index
   .type irq\index, @function
   irq\index:
      cli
      push $0x00
      push $\entry
      jmp irq_common_stub
.endm

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

irq_common_stub:
   pusha

   push %ds
   push %es
   push %fs
   push %gs

   mov $0x10, %ax
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs

   mov %esp, %eax
   push %eax
   mov $irq_handler, %eax

   call *%eax
   pop %eax

   pop %gs
   pop %fs
   pop %es
   pop %ds
   popa

   add $8, %esp
   iret
