#include "paging.h"
#include <stdint.h>

#define PAGE_PRESENT 0x1
#define PAGE_RW      0x2
#define PAGE_USER    0x4
#define PAGE_PS      0x80

static uint64_t pdpt[4] __attribute__((aligned(32)));
static uint64_t pd[4][512] __attribute__((aligned(4096)));

static void enable_pae(uint32_t pdpt_addr)
{
    asm volatile(
        "mov %0, %%cr3\n"
        "mov %%cr4, %%eax\n"
        "or $0x30, %%eax\n" /* PSE PAE */
        "mov %%eax, %%cr4\n"
        "mov %%cr0, %%eax\n"
        "or $0x80000000, %%eax\n"
        "mov %%eax, %%cr0\n"
        :
        : "r"(pdpt_addr)
        : "eax"
    );
}

void paging_init(void)
{
    for (int i = 0; i < 4; ++i)
    {
        pdpt[i] = ((uint32_t)pd[i]) | PAGE_PRESENT;
        for (int j = 0; j < 512; ++j)
        {
            uint64_t addr = ((uint64_t)i << 30) | ((uint64_t)j << 21);
            pd[i][j] = addr | PAGE_PRESENT | PAGE_RW | PAGE_PS | PAGE_USER;
        }
    }

    enable_pae((uint32_t)pdpt);
}
