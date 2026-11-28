// FUNCTION: SLPM 0x001B21F0  size 96  core 80
extern char D_0022E92C[];
extern void FUN_001b1398(void);
extern void FUN_001cfa78(int);

int FUN_001b21f0(void)
{
    int r;

    r = 1;
    switch (*(int *)D_0022E92C) {
    case 0:
        FUN_001b1398();
        break;
    case 1:
        break;
    case 2:
        FUN_001b1398();
        break;
    default:
        r = 0;
        break;
    }
    FUN_001cfa78(-1);
    return r;
}
