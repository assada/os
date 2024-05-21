.section .text
.global idt_load
idt_load:
    lidt [idtp]
    ret
