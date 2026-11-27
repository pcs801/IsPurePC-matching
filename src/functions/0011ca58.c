// FUNCTION: SLPM 0x0011CA58  size 208
extern int FUN_00115730(int v);
extern int FUN_0012bdb0(unsigned char a, int b, int c, int d, int e, int f);
extern int FUN_00117dc0(char *p);

int FUN_0011ca58(char *c)
{
    char *r = *(char **)(*(char **)(c + 0x44) + 8);
    int a = FUN_00115730(*(short *)(r + 6));
    unsigned short lim = *(unsigned short *)(r + 8);
    int c4, c8, cA;

    FUN_00115730(*(short *)(r + 2));
    if ((int)lim < a)
        a = (int)lim;
    c4 = FUN_00115730(*(short *)(r + 4));
    c8 = FUN_00115730(*(short *)(r + 8));
    cA = FUN_00115730(*(short *)(r + 0xA));
    FUN_0012bdb0(*(unsigned char *)(r + 1), a, c4, c8, cA, cA);
    *(int *)(*(char **)(c + 0x44) + 8) += 0xC;
    FUN_00117dc0(c);
    return 0;
}
