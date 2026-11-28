// FUNCTION: SLPM 0x00210580  size 88  core 88
extern int FUN_0020f130(void);
extern int FUN_00210530(void *p, int v);
extern void FUN_0020f180(void);

int FUN_00210580(char *p, int v)
{
    int t = FUN_0020f130();
    int r = FUN_00210530(p, v);

    if (t != 0)
        FUN_0020f180();
    return r;
}
