extern void FUN_001ccb00(int a0);
extern void FUN_001ce988(void);
extern void FUN_001fbb84(char *p, int a1, int a2);
extern void FUN_001ce9a0(void);

void FUN_001b2bd0(char *p)
{
    if (p != 0) {
        if (*(int **)(p + 4) != 0) {
            FUN_001ccb00(*(int *)(p + 4));
            *(int *)(p + 4) = 0;
        }
        FUN_001ce988();
        FUN_001fbb84(p, 0, 172);
        FUN_001ce9a0();
    }
}
