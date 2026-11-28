// FUNCTION: SLPM 0x002103D8  size 72  core 72
extern int FUN_0020f130(void *p);
extern int FUN_00210368(void *p);
extern void FUN_0020f180(void);

int FUN_002103d8(void *p)
{
    int r;
    int t;

    t = FUN_0020f130(p);
    r = FUN_00210368(p);
    if (t != 0)
        FUN_0020f180();
    return r;
}
