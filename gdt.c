#include "gdt.h"
#include "string.h"

#define GDT_ENTRY 6

Gdt_entry gdt[GDT_ENTRY];
Gdt_ptr gdt_ptr;

extern void gdt_flush(void);

Tss_entry tss;
extern void tss_flush(void);

void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = limit & 0xFFFF;

    gdt[num].granularity = (limit >> 16) & 0xF;
    gdt[num].granularity |= (granularity & 0xF0);

    gdt[num].access = access;
}

void tss_set_gate(uint32_t num, uint16_t ss0, uint32_t esp0)
{
    uint32_t base = (uint32_t)&tss;
    uint32_t limit = base + sizeof(Tss_entry);
    gdt_set_gate(num, base, limit, 0xE9, 0x0);
    memset(&tss, 0x0, sizeof(Tss_entry));
    tss.ss0 = ss0;
    tss.esp0 = esp0;

    tss.cs = 0x1B;
    tss.ss = 0x23;
    tss.es = 0x23;
    tss.ds = 0x23;
    tss.fs = 0x23;
    tss.gs = 0x23;
}

void gdt_install()
{

    gdt_set_gate(0, 0x0, 0x0, 0x0, 0x0);          // Null segment
    gdt_set_gate(1, 0x0, 0xFFFFFFFF, 0x9A, 0xC0); // 0x08 Kernel code segment
    gdt_set_gate(2, 0x0, 0xFFFFFFFF, 0x92, 0xC0); // 0x10 Kernel data segment
    gdt_set_gate(3, 0x0, 0xFFFFFFFF, 0xFA, 0xC0); // 0x18 User code segment
    gdt_set_gate(4, 0x0, 0xFFFFFFFF, 0xF2, 0xC0); // 0x20 User data segment

    tss_set_gate(5, 0x10, 0);

    gdt_ptr.limit = (sizeof(Gdt_entry) * GDT_ENTRY) - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    gdt_flush();
    tss_flush();
}
