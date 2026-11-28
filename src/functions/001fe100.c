extern int D_002561B8;
extern void FUN_001fd1e8(int a0, int a1, int a2);
extern int FUN_001fe100(int a0, int a1);
extern void FUN_001f9090(int a0);

void FUN_001fe100(int a0, int a1)
{
    int g = D_002561B8;

    FUN_001fd1e8(g, a0, a1);
}

void FUN_001fe128(int a0, int a1)
{
    FUN_001f9090(FUN_001fe100(a0, a1));
}
