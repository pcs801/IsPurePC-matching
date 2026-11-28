// FUNCTION: SLPM 0x0011d188  size 88  core 84  -G8
extern int D_00270CAC;
extern void FUN_00117dc0(void);

int FUN_0011d188(char *p)
{
    int a = *(int *)(p + 0x44);
    unsigned char *q = *(unsigned char **)(a + 8);
    unsigned char idx = q[1];
    unsigned short val = *(unsigned short *)(q + 2);

    *(int *)(a + 8) = (int)(q + 4);
    *(unsigned short *)(D_00270CAC + idx * 12 + 0x3F488) = val;
    FUN_00117dc0();
    return 0;
}
