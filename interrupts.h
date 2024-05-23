#ifndef INTERUPTS_H
#define INTERUPTS_H

#include <stdint.h>

typedef struct stack_t Stack;
struct stack_t
{
    /* Pushed the segs last */
    uint32_t gs, fs, es, ds;
    /* Pushed by 'pusha' */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    /* Our 'push #' and ecodes do this */
    uint32_t id, err_code;
    /* Pushed by the processor automatically */
    uint32_t eip, cs, eflags, useresp, ss;
};

#define NB_ISR_ROUTINES 256

void isr_install_handler(uint8_t isr, void (*handler)(Stack *registers));
void isr_uninstall_handler(uint8_t isr);
void isr_call_handler(Stack *registers);
void isr_install(void);

#define NB_IRQ_ROUTINES 16

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_CMD PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_CMD PIC2
#define PIC2_DATA (PIC2 + 1)
#define PIC1_OFFSET 0x20
#define PIC2_OFFSET 0x28

#define PIC_EOI 0x20

#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10
#define ICW4_8086 0x01

void irq_install_handler(uint8_t irq, void (*handler)(Stack *registers));
void irq_uninstall_handler(uint8_t irq);
void irq_call_handler(Stack *registers);
void irq_install(void);

#endif
