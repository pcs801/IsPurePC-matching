extern void FUN_001ab1c0(int a0, int a1, int a2, int a3);
extern void FUN_001ab258(int a0, int a1, int a2, int a3);

void FUN_001ab358(int a0, int a1, int a2, int a3, int a4, int a5)
{
    if (a5 & 2)
        FUN_001ab1c0(a0, a1, a2, a3);
    else
        FUN_001ab258(a0, a1, a2, a3);
}
