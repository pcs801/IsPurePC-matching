// FUNCTION: SLPM 0x001B6258  size 128  core 128
extern void FUN_001c3720(void);
extern void FUN_001c3748(int a0);
extern void FUN_001c3778(int a0);
extern void FUN_001cf618(void *p);

void FUN_001b6258(void)
{
    FUN_001c3720();
}

void FUN_001b6270(char *p)
{
    if (p != 0) {
        FUN_001c3748(*(int *)(p + 4));
        FUN_001c3778(*(int *)p);
    } else {
        FUN_001c3748(0);
        FUN_001c3778(0);
    }
}

void FUN_001b62c0(int a0, int a1)
{
    FUN_001cf618((void *)a1);
}
