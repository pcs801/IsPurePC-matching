SECTIONS
{
    HIDDEN(__romPos = 0);
    _0_ROM_START = __romPos;
    _0_VRAM = ADDR(._0);
    ._0 : AT(_0_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        _0_DATA_START = .;
        build/assets/0.bin.o(.data);
        _0_DATA_END = .;
        _0_DATA_SIZE = ABSOLUTE(_0_DATA_END - _0_DATA_START);
    }
    __romPos += SIZEOF(._0);
    _0_ROM_END = __romPos;
    _0_VRAM_END = .;

    text_ROM_START = __romPos;
    text_VRAM = ADDR(.text);
    .text 0x100000 : AT(text_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        text_TEXT_START = .;
        build/asm/1000.s.o(.text);
        . = ALIGN(., 16);
        text_TEXT_END = .;
        text_TEXT_SIZE = ABSOLUTE(text_TEXT_END - text_TEXT_START);
        text_DATA_START = .;
        build/asm/1000.s.o(.data);
        . = ALIGN(., 16);
        text_DATA_END = .;
        text_DATA_SIZE = ABSOLUTE(text_DATA_END - text_DATA_START);
        text_RODATA_START = .;
        build/asm/1000.s.o(.rodata);
        . = ALIGN(., 16);
        text_RODATA_END = .;
        text_RODATA_SIZE = ABSOLUTE(text_RODATA_END - text_RODATA_START);
    }
    text_bss_VRAM = ADDR(.text_bss);
    .text_bss (NOLOAD) : SUBALIGN(16)
    {
        FILL(0x00000000);
        text_BSS_START = .;
        build/asm/1000.s.o(.bss);
        . = ALIGN(., 16);
        text_BSS_END = .;
        text_BSS_SIZE = ABSOLUTE(text_BSS_END - text_BSS_START);
    }
    __romPos += SIZEOF(.text);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    text_ROM_END = __romPos;
    text_VRAM_END = .;

    ctors_ROM_START = __romPos;
    ctors_VRAM = ADDR(.ctors);
    .ctors 0x21299C : AT(ctors_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        ctors_DATA_START = .;
        build/assets/ctors.bin.o(.data);
        ctors_DATA_END = .;
        ctors_DATA_SIZE = ABSOLUTE(ctors_DATA_END - ctors_DATA_START);
    }
    __romPos += SIZEOF(.ctors);
    ctors_ROM_END = __romPos;
    ctors_VRAM_END = .;

    dtors_ROM_START = __romPos;
    dtors_VRAM = ADDR(.dtors);
    .dtors 0x2129A4 : AT(dtors_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        dtors_DATA_START = .;
        build/assets/dtors.bin.o(.data);
        dtors_DATA_END = .;
        dtors_DATA_SIZE = ABSOLUTE(dtors_DATA_END - dtors_DATA_START);
    }
    __romPos += SIZEOF(.dtors);
    dtors_ROM_END = __romPos;
    dtors_VRAM_END = .;

    reginfo_ROM_START = __romPos;
    reginfo_VRAM = ADDR(.reginfo);
    .reginfo 0x2129AC : AT(reginfo_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        reginfo_DATA_START = .;
        build/assets/reginfo.bin.o(.data);
        reginfo_DATA_END = .;
        reginfo_DATA_SIZE = ABSOLUTE(reginfo_DATA_END - reginfo_DATA_START);
    }
    __romPos += SIZEOF(.reginfo);
    reginfo_ROM_END = __romPos;
    reginfo_VRAM_END = .;

    data_ROM_START = __romPos;
    data_VRAM = ADDR(.data);
    .data 0x212A00 : AT(data_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        data_DATA_START = .;
        build/assets/data.bin.o(.data);
        data_DATA_END = .;
        data_DATA_SIZE = ABSOLUTE(data_DATA_END - data_DATA_START);
    }
    __romPos += SIZEOF(.data);
    data_ROM_END = __romPos;
    data_VRAM_END = .;

    eh_frame_ROM_START = __romPos;
    eh_frame_VRAM = ADDR(.eh_frame);
    .eh_frame 0x257D08 : AT(eh_frame_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        eh_frame_DATA_START = .;
        build/assets/eh_frame.bin.o(.data);
        eh_frame_DATA_END = .;
        eh_frame_DATA_SIZE = ABSOLUTE(eh_frame_DATA_END - eh_frame_DATA_START);
    }
    __romPos += SIZEOF(.eh_frame);
    eh_frame_ROM_END = __romPos;
    eh_frame_VRAM_END = .;

    rodata_ROM_START = __romPos;
    rodata_VRAM = ADDR(.rodata);
    .rodata 0x257D80 : AT(rodata_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        rodata_DATA_START = .;
        build/assets/rodata.bin.o(.data);
        rodata_DATA_END = .;
        rodata_DATA_SIZE = ABSOLUTE(rodata_DATA_END - rodata_DATA_START);
    }
    __romPos += SIZEOF(.rodata);
    rodata_ROM_END = __romPos;
    rodata_VRAM_END = .;

    lit4_ROM_START = __romPos;
    lit4_VRAM = ADDR(.lit4);
    .lit4 0x26FA00 : AT(lit4_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        lit4_DATA_START = .;
        build/assets/lit4.bin.o(.data);
        lit4_DATA_END = .;
        lit4_DATA_SIZE = ABSOLUTE(lit4_DATA_END - lit4_DATA_START);
    }
    __romPos += SIZEOF(.lit4);
    lit4_ROM_END = __romPos;
    lit4_VRAM_END = .;

    sdata_ROM_START = __romPos;
    sdata_VRAM = ADDR(.sdata);
    .sdata 0x26FB80 : AT(sdata_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        sdata_DATA_START = .;
        build/assets/sdata.bin.o(.data);
        sdata_DATA_END = .;
        sdata_DATA_SIZE = ABSOLUTE(sdata_DATA_END - sdata_DATA_START);
    }
    __romPos += SIZEOF(.sdata);
    sdata_ROM_END = __romPos;
    sdata_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
