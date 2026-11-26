extern int D_00270AA8;
extern unsigned char D_456740[];
extern int D_456540[];
extern unsigned char D_4567C0[];
extern unsigned char D_456840[];

void FUN_00108478(unsigned char a0, unsigned char a1, unsigned char a2)
{
    int i = D_00270AA8;
    if (i < 0x80) {
        D_00270AA8 = i + 1;
        D_456740[i] = a0;
        D_456540[i] = *(int *)0x10000000;
        D_4567C0[i] = a1;
        D_456840[i] = a2;
    }
}
