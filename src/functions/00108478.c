// FUNCTION: SLPM 0x00108478  size 112  core 100
extern int D_00270AA8;
extern unsigned char D_456740[];
extern int D_456540[];
extern unsigned char D_4567C0[];
extern unsigned char D_456840[];

void FUN_00108478(unsigned char a0, unsigned char a1, unsigned char a2)
{
    if (D_00270AA8 < 0x80) {
        D_456740[D_00270AA8] = a0;
        D_456540[D_00270AA8] = *(int *)0x10000000;
        D_4567C0[D_00270AA8] = a1;
        D_456840[D_00270AA8] = a2;
        D_00270AA8 = D_00270AA8 + 1;
    }
}
