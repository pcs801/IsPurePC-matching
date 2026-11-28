// FUNCTION: SLPM 0x001BE160  size 76  core 76
extern int FUN_001bc620(void);

int FUN_001be160(void)
{
    char *p = (char *)FUN_001bc620();
    int (*fp)(int, int, int, int);

    if (p == 0)
        return 0;
    fp = *(int (**)(int, int, int, int))(p + 96);
    if (fp != 0)
        fp(0, 100, 0, 0);
    return 0;
}
