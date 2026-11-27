// FUNCTION: SLPM 0x001DBB18  size 400 (GS display-mode / CRT setup entry)
struct Conf {
    short f0;
    short f2;
    short f4;
    short f6;
    int f8;
    int fC;
};

extern struct Conf *FUN_001dbca8(void);
extern void FUN_00205ce0(int imr);
extern void FUN_00206480(int n);
extern void FUN_002056a0(int n, int h);
extern void FUN_002055a0(int a, int b, int c);

void FUN_001dbb18(short mode, short a, short b, short c)
{
    unsigned long long *gs = (unsigned long long *)0x12001000;
    struct Conf *p;

    switch (mode) {
    case 0:
        p = FUN_001dbca8();
        *gs = 0x200ULL;
        p->f0 = a;
        p->f2 = b;
        p->f6 = (short)((*gs >> 16) & 0xFF);
        FUN_00205ce0(0xFF00);
        p->f4 = (c != 0);
        if (p->f8 != 0) {
            FUN_00206480(2);
            FUN_002056a0(2, p->fC);
            p->fC = 0;
            p->f8 = 0;
        }
        FUN_002055a0(a & 1, b & 0xFF, c & 1);
        break;
    case 1:
        *gs = 0x100ULL;
        break;
    case 5:
        p = FUN_001dbca8();
        p->f4 = (c != 0);
        p->f0 = a;
        p->f2 = b;
        p->f6 = (short)((*gs >> 16) & 0xFF);
        FUN_002055a0(a & 1, b & 0xFF, c & 1);
        break;
    }
}
