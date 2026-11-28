extern char D_001B62C0[];
extern char D_00265D50[];
extern char D_001C4CE0[];
extern void FUN_001bdc48(char *a0, int a1);
extern void FUN_001bc4c0(char *a0, char *a1, int a2);
extern int D_002304A4;

void FUN_001b62d8(void)
{
    FUN_001bdc48(D_001B62C0, 0);
    FUN_001bc4c0(D_00265D50, D_001C4CE0, 0);
}

int FUN_001b6310(void)
{
    return D_002304A4;
}

void FUN_001b6320(int v)
{
    D_002304A4 = v;
}
