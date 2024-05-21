.section .text
.global pit_handler_asm

pit_handler_asm:
    push %eax               # Save the registers used by the C handler
    push %ecx
    push %edx
    call pit_handler        # Call the C handler
    pop %edx                # Restore the registers in reverse order
    pop %ecx
    pop %eax
    iret                    # Return from interrupt
