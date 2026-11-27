// FUNCTION: SLPM 0x001DD010  size 1680 (core 1676)  GS texture-format dispatcher
// NOT COMPLETED: 1676 bytes / 420 instructions, entry dispatches through
// jtbl_0026BF00[psm] with 46 table entries pointing at the common tail 0x001DD1EC.
// The tail (0x001DD1EC..0x001DD260) is still undocumented, and a compiler-generated
// jump table emits HI16/LO16 relocations against the .rodata section symbol, which
// tools/build.py cannot resolve (seen in 0x00107DB8, t81), so this function is
// blocked twice over. Structure recorded: psm = (desc[0x20] >> 24) & 0x3F,
// w = desc[0x40] & 0xFFF, h = (desc[0x40] >> 32) & 0xFFF; five case groups
// (0/48/49 4bpp, 1/49 3bpp, 2/10/50/58 2bpp, 19/27 1bpp, 20/36/44 bitmap) each
// produce (a1=aligned width, s2=full blocks, s1=block remainder, s3=byte remainder,
// s6=extra blocks) and fall into the shared tail.
struct Desc {
    unsigned char pad[0x40];
};

int FUN_001dd010(struct Desc *desc)
{
    unsigned int psm = (*(unsigned int *)((char *)desc + 0x20) >> 24) & 0x3F;

    switch (psm) {
    case 0:
    case 48:
    case 49:
    case 1:
    case 2:
    case 10:
    case 50:
    case 58:
    case 19:
    case 27:
    case 20:
    case 36:
    case 44:
        break;
    }
    return 0;
}
