typedef unsigned short u16;

extern int *D_00270CAC;

void FUN_001157f8(int p, int value)
{
    unsigned short v;
    short val;
    char *base;

    v = (unsigned short)p;
    val = (short)value;
    base = (char *)D_00270CAC;
    switch ((unsigned short)v & 0xC000) {
    case 0x4000:
        switch ((u16)(v & 0x2000)) {
        case 0:
            *(short *)(base + ((u16)v & 0x1FFF) * 2) = val;
            break;
        case 0x2000:
            *(short *)(base + 0x220 + ((u16)v & 0x1FFF) * 2) = val;
            break;
        }
        break;
    case 0x8000:
        switch ((u16)(v & 0x2000)) {
        case 0:
            switch (val & 1) {
            case 0:
                *(unsigned char *)(base + 0x200 + (((u16)v & 0x1FFF) >> 3)) &=
                    ~(1 << (((u16)v & 0x1FFF) - ((((u16)v & 0x1FFF) >> 3) << 3)));
                break;
            case 1:
                *(unsigned char *)(base + 0x200 + (((u16)v & 0x1FFF) >> 3)) |=
                    (1 << (((u16)v & 0x1FFF) - ((((u16)v & 0x1FFF) >> 3) << 3)));
                break;
            }
            break;
        case 0x2000:
            switch (val & 1) {
            case 0:
                *(unsigned char *)(base + 0x420 + (((u16)v & 0x1FFF) >> 3)) &=
                    ~(1 << (((u16)v & 0x1FFF) - ((((u16)v & 0x1FFF) >> 3) << 3)));
                break;
            case 1:
                *(unsigned char *)(base + 0x420 + (((u16)v & 0x1FFF) >> 3)) |=
                    (1 << (((u16)v & 0x1FFF) - ((((u16)v & 0x1FFF) >> 3) << 3)));
                break;
            }
            break;
        }
        break;
    }
}
