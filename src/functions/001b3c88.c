extern void FUN_001cd2b8(void);
extern void FUN_001cd300(int a0);

void FUN_001b3c88(void)
{
    FUN_001cd2b8();
}

void FUN_001b3ca0(char *p)
{
    FUN_001cd300(*(int *)(p + 4));
}
