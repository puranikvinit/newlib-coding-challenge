ENTRY(_start)

SECTIONS
{
    . = 0x80000000;
    .text : {
        *(.text)
        *(.text.*)
    }

    . = 0x80010000;
    .data : {
        *(.data)
        *(.data.*)
    }

    . = 0x80020000;
    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }

    . = 0x80030000;
    .stack (NOLOAD) : {
        . = ALIGN(8);
        _stack_start = .;
        . = . + 0x4000; /* 16 KB stack */
        _stack_end = .;
    }
    
    _text_start = ADDR(.text);
    _text_end = ADDR(.text) + SIZEOF(.text);
    _data_start = ADDR(.data);
    _data_end = ADDR(.data) + SIZEOF(.data);
    _bss_start = ADDR(.bss);
    _bss_end = ADDR(.bss) + SIZEOF(.bss);
}
