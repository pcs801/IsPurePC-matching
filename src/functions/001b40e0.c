// FUNCTION: SLPM 0x001B40E0  size 80  core 80
extern int D_0022F410;
extern char D_0022F430[];
extern void FUN_001fbb84(void *a0, int a1, int a2);

int FUN_001b40e0(void)
{
    if (++D_0022F410 == 1) {
        FUN_001fbb84(D_0022F430, 0, 0x1040);
        return 1;
    }
    return 0;
}
