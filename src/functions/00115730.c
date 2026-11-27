typedef unsigned short u16;

extern int *D_00270CAC;

int FUN_00115730(int p)
{
    short v;
    int r;
    char *base;

    v = (short)p;
    r = 0;
    base = (char *)D_00270CAC;
    switch ((unsigned short)v & 0xC000) {
    case 0x4000:
        switch ((u16)(v & 0x2000)) {
        case 0:
            r = *(short *)(base + ((u16)v & 0x1FFF) * 2);
            break;
        case 0x2000:
            r = *(short *)(base + 0x220 + ((u16)v & 0x1FFF) * 2);
            break;
        }
        break;
    case 0x8000:
        switch ((u16)(v & 0x2000)) {
        case 0:
            r = (*(unsigned char *)(base + 0x200 + (((u16)v & 0x1FFF) >> 3))
                 >> (((u16)v & 0x1FFF) - ((((u16)v & 0x1FFF) >> 3) << 3))) & 1;
            break;
        case 0x2000:
            r = (*(unsigned char *)(base + 0x420 + (((u16)v & 0x1FFF) >> 3))
                 >> (((u16)v & 0x1FFF) - ((((u16)v & 0x1FFF) >> 3) << 3))) & 1;
            break;
        }
        break;
    default:
        r = v;
        break;
    }
    return r;
}
