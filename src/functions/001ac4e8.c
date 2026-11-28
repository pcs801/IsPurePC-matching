extern int FUN_0020f130(void);
extern void FUN_0020f180(void);
extern void FUN_002059b0(int a0);
extern int D_002241B8;

void FUN_001ac4e8(void)
{
    int r = FUN_0020f130();
    int s = D_002241B8;

    D_002241B8 = -1;
    if (r != 0)
        FUN_0020f180();
    if (s >= 0)
        FUN_002059b0(s);
}
