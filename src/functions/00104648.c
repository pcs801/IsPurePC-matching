// FUNCTION: SLPM 0x00104648  size 224
typedef unsigned short u16;

extern char D_A94700[];
extern char D_1B73FC0[];
extern char D_1B74080[];

int FUN_00104648(int p)
{
    short v = (short)p;
    int r = 0;
    switch ((unsigned short)v & 0xC000) {
    case 0x4000:
        switch ((u16)(v & 0x2000)) {
        case 0: r = *(short *)((char *)D_A94700 + ((u16)v & 0x1FFF) * 2); break;
        case 0x2000: r = *(short *)((char *)D_1B73FC0 + ((u16)v & 0x1FFF) * 2); break;
        }
        break;
    case 0x8000:
        switch ((u16)(v & 0x2000)) {
        case 0: r = (*(unsigned char *)((char *)D_A94700 + 0x40 + (((u16)v & 0x1FFF) >> 3))
                     >> (((u16)v & 0x1FFF) - ((((u16)v & 0x1FFF) >> 3) << 3))) & 1; break;
        case 0x2000: r = (*(unsigned char *)((char *)D_1B74080 + (((u16)v & 0x1FFF) >> 3))
                     >> (((u16)v & 0x1FFF) - ((((u16)v & 0x1FFF) >> 3) << 3))) & 1; break;
        }
        break;
    default:
        r = v;
        break;
    }
    return r;
}
