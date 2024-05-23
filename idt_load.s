.section .text
.align 4

.global idt_load
.type idt_load, @function
idt_load:
    lidt idtp
    ret
