#ifndef GDT_H
#define GDT_H

#include <stdint.h>

extern void* stack_top;

//! set access bit
#define I86_GDT_DESC_ACCESS 0x0001	//00000001

//! descriptor is readable and writable. default: read only
#define I86_GDT_DESC_READWRITE 0x0002  //00000010

//! set expansion direction bit
#define I86_GDT_DESC_EXPANSION 0x0004  //00000100

//! executable code segment. Default: data segment
#define I86_GDT_DESC_EXEC_CODE 0x0008  //00001000

//! set code or data descriptor. defult: system defined descriptor
#define I86_GDT_DESC_CODEDATA 0x0010  //00010000

//! set dpl bits
#define I86_GDT_DESC_DPL 0x0060	 //01100000

//! set "in memory" bit
#define I86_GDT_DESC_MEMORY 0x0080	//10000000

/**	gdt descriptor grandularity bit flags	***/

//! masks out limitHi (High 4 bits of limit)
#define I86_GDT_GRAND_LIMITHI_MASK 0x0f	 //00001111

//! set os defined bit
#define I86_GDT_GRAND_OS 0x10  //00010000

//! set if 32bit. default: 16 bit
#define I86_GDT_GRAND_32BIT 0x40  //01000000

//! 4k grandularity. default: none
#define I86_GDT_GRAND_4K 0x80  //10000000

typedef struct gdt_entry_t Gdt_entry;
struct gdt_entry_t
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

typedef struct gdt_ptr_t Gdt_ptr;
struct gdt_ptr_t
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);
void gdt_install();

void set_kernel_stack(uint32_t stack);

typedef struct tss_entry_t Tss_entry;
struct tss_entry_t
{
    uint32_t prevTss;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap;
    uint16_t iopb_off;
} __attribute__((packed));

#endif