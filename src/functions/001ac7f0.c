extern void FUN_001ac878(int a0, int a1, int a2, int a3);
extern void FUN_001af7d0(int a0, int a1, int a2, int a3);
extern void FUN_001af7e8(void);

void FUN_001ac7f0(int a0, int a1, int a2)
{
    FUN_001ac878(a0, a1, 0, a2);
}

int FUN_001ac810(int a0, int a1, int a2, int a3)
{
    int r;

    FUN_001af7d0(a0, a1, a2, a3);
    r = FUN_001ac878(a0, a1, a2, a3);
    FUN_001af7e8();
    return r;
}
