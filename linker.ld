ENTRY(_start)

SECTIONS
{
   . = 1M;

   kernel_start = .;

   .text BLOCK(4K) : ALIGN(4K)
   {
      *(.multiboot)
      *(.text)
   }

   .rodata BLOCK(4K) : ALIGN(4K)
   {
      *(.rodata)
   }

   .data BLOCK(4K) : ALIGN(4K)
   {
      *(.data)
   }

   .bss BLOCK(4K) : ALIGN(4K)
   {
      *(.bss)
      *(.stack)
   }

   kernel_end = .;
}
