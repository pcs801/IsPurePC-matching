// FUNCTION: SLPM 0x001BBB80  size 64  core 60
extern char D_0023051C[];
extern void FUN_001d0b78(void);

void FUN_001bbb80(void)
{
    int *p;

    p = (int *)D_0023051C;
    if (*p == 1)
        FUN_001d0b78();
    *p = *p - 1;
}
