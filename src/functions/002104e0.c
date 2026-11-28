// FUNCTION: SLPM 0x002104E0  size 76  core 76
extern int FUN_0020f130(void *p);
extern int FUN_00210420(void *p);
extern void FUN_0020f180(void);

int FUN_002104e0(char *p)
{
    int t = FUN_0020f130(p);
    int r = FUN_00210420(p);

    if (t != 0)
        FUN_0020f180();
    return r;
}
