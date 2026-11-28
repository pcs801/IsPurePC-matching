// FUNCTION: SLPM 0x001CBA48  size 96  core 88  (splat merged two functions)
//  0x1CBA48: --*D_0241AA4; if (==0) { FUN_001cb960(); FUN_001fbb84(D_0245C30, 0, 8); }
//  0x1CBAA0: separate function (lui v0,0x86 / ...)
extern char D_0241AA4[];
extern char D_0245C30[];
extern void FUN_001cb960(void);
extern void FUN_001fbb84(char *, int, int);

void FUN_001cba48(void)
{
    *(int *)D_0241AA4 = *(int *)D_0241AA4 - 1;
    if (*(int *)D_0241AA4 != 0)
        return;
    FUN_001cb960();
    FUN_001fbb84(D_0245C30, 0, 8);
}
