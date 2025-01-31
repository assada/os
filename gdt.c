#include "gdt.h"
#include "string.h"

#define GDT_ENTRY 6

Gdt_entry gdt[GDT_ENTRY];
Gdt_ptr gdtp;

extern void gdt_flush(uint32_t);

Tss_entry tss;
extern void tss_flush(void);

static void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = limit & 0xFFFF;

    gdt[num].granularity = (limit >> 16) & 0xF;
    gdt[num].granularity |= (granularity & 0xF0);

    gdt[num].access = access;
}

void tss_install(uint8_t num, uint16_t kernel_ss, uint16_t kernel_esp)
{
    uint32_t base = (uint32_t)&tss;
    uint32_t limit = sizeof(Tss_entry);

    memset(&tss, 0, sizeof(Tss_entry));

    tss.ss0 = kernel_ss;
    tss.esp0 = kernel_esp;
    
    tss.cs = 0x1b;
    tss.ss = 0x23;
    tss.ds = 0x23;
    tss.es = 0x23;
    tss.fs = 0x23;
    tss.gs = 0x23;
    
    tss.iopb_off = sizeof(Tss_entry);

    gdt_set_gate(num, base, limit, I86_GDT_DESC_ACCESS | I86_GDT_DESC_EXEC_CODE | I86_GDT_DESC_DPL | I86_GDT_DESC_MEMORY, 0x00);
}

void gdt_install()
{
    gdtp.limit = (sizeof(Gdt_entry) * GDT_ENTRY) - 1;
    gdtp.base = (uint32_t)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);

    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    tss_install(5, 0x10, (uint32_t)&stack_top);

    gdt_flush((uint32_t)&gdtp);
    tss_flush();
}
