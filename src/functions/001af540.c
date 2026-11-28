// FUNCTION: SLPM 0x001AF540  size 112  core 108
extern int FUN_001fba40(int a0, char *a1, int a2);
extern char D_00265248[];
extern int D_00243768;

int FUN_001af540(unsigned char *p)
{
    if (FUN_001fba40((int)p, D_00265248, 3) != 0)
        return -4;
    return p[4] | (p[5] << 8) | (p[6] << 16) | (p[7] << 24);
}

void FUN_001af5a0(int v)
{
    D_00243768 = v;
}
