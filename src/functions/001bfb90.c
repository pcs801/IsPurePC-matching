// FUNCTION: SLPM 0x001BFB90  size 120  core 104  (splat merged two functions)
//  0x1BFB90: *D_0863540 = a0; FUN_00209838(D_00230EA0, 3, 0, D_0863540, 4, D_0863640, 0, 0, 0);
//  0x1BFBE0: return ++*D_00230610;
extern char D_0863540[];
extern char D_0863640[];
extern char D_00230EA0[];
extern char D_00230610[];
extern void FUN_00209838(char *, int, int, char *, int, char *, int, int, int);

void FUN_001bfb90(int a0)
{
    *(int *)D_0863540 = a0;
    FUN_00209838(D_00230EA0, 3, 0, D_0863540, 4, D_0863640, 0, 0, 0);
}

int FUN_001bfbe0(void)
{
    return ++*(int *)D_00230610;
}
