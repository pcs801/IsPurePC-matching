typedef unsigned short u16;

extern int *D_000AEC2C;
extern int *D_000AEC34;
extern int *D_000AEC3C;
extern int *D_000AEC44;

int FUN_00115938(int p)
{
    unsigned short v;
    int r;

    v = (unsigned short)p;
    r = 0;
    switch ((unsigned short)v & 0xC000) {
    case 0x4000:
        switch ((u16)(v & 0x2000)) {
        case 0:
            r = D_000AEC34[(u16)v & 0x1FFF];
            break;
        case 0x2000:
            r = D_000AEC44[(u16)v & 0x1FFF];
            break;
        }
        break;
    case 0x8000:
        switch ((u16)(v & 0x2000)) {
        case 0:
            r = D_000AEC2C[(u16)v & 0x1FFF];
            break;
        case 0x2000:
            r = D_000AEC3C[(u16)v & 0x1FFF];
            break;
        }
        break;
    }
    return r;
}
