// FUNCTION: SLPM 0x002109E8  size 76  core 76
extern int FUN_0020f130(void *p);
extern int FUN_00210978(void *p);
extern void FUN_0020f180(void);

int FUN_002109e8(char *p)
{
    int t = FUN_0020f130(p);
    int r = FUN_00210978(p);

    if (t != 0)
        FUN_0020f180();
    return r;
}
