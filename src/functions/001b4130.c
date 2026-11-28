// FUNCTION: SLPM 0x001b4130  size 80  core 76
extern int D_0022F410;
extern char D_0022F430[];
extern void FUN_001fbb84(char *a0, int a1, int a2);

void FUN_001b4130(void)
{
    if (--D_0022F410 == 0)
        FUN_001fbb84(D_0022F430, 0, 0x1040);
}
