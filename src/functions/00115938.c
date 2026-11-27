typedef unsigned short u16;

extern int *D_B1EC2C;
extern int *D_B1EC34;
extern int *D_B1EC3C;
extern int *D_B1EC44;

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
            return D_B1EC34[(u16)v & 0x1FFF];
        case 0x2000:
            return D_B1EC44[(u16)v & 0x1FFF];
        }
        break;
    case 0x8000:
        switch ((u16)(v & 0x2000)) {
        case 0:
            return D_B1EC2C[(u16)v & 0x1FFF];
        case 0x2000:
            return D_B1EC3C[(u16)v & 0x1FFF];
        }
        break;
    }
    return r;
}
