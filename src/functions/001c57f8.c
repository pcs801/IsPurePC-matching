// FUNCTION: SLPM 0x001c57f8  size 112  core 112
extern void FUN_001b6fa0(void);
extern void FUN_001b1970(void);
extern void FUN_001d2d40(int a0);
extern void FUN_001d2bb0(int a0);
extern void FUN_001b1988(void);

void FUN_001c57f8(char *p)
{
    char *a = *(char **)((char *)*(char **)(p + 4) + 4);
    int v = *(int *)(a + 0xE8);

    if (v == 0)
        return;
    FUN_001b6fa0();
    FUN_001b1970();
    FUN_001d2d40(v);
    *(int *)(a + 0xE8) = 0;
    FUN_001d2bb0(0);
    FUN_001b1988();
}
