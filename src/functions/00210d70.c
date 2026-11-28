// FUNCTION: SLPM 0x00210d70  size 80  core 76
extern char D_872680[];

void FUN_00210d70(void)
{
    char *base = D_872680;
    char *p = base + 0x400;
    char *q = base + 0x3F0;
    int i;

    *(int *)0x00872A80 = (int)base;
    for (i = 0x3F; i >= 0; i--) {
        *(int *)q = (int)p;
        q -= 0x10;
        p -= 0x10;
    }
    *(int *)(base + 0x3F0) = 0;
}
