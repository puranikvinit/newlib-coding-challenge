.section .text
.global _start
.global main

_start:
    la sp, _stack_end # Setup stack pointer

    # BSS section init
    la a0, _bss_start
    la a1, _bss_end

1:
    beq a0, a1, 2f
    sw zero, 0(a0)
    addi a0, a0, 4
    j 1b

    # Jump to the test
2:
    call main
    j .
