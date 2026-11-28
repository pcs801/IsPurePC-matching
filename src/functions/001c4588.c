// FUNCTION: SLPM 0x001C4588  size 144  core 112  (splat merged two functions)
//  0x1C4588: if (p == 0) { FUN_001c4708(D_002686A0); return -1; } return *(int*)(p + 0x14);
//  0x1C45B8: three-global setter (zero branch / store branch)
extern char D_002686A0[];
extern char D_00232624[];
extern char D_00232628[];
extern char D_0023262C[];
extern void FUN_001c4708(char *);

int FUN_001c4588(char *p)
{
    if (p == 0) {
        FUN_001c4708(D_002686A0);
        return -1;
    }
    return *(int *)(p + 0x14);
}

void FUN_001c45b8(int a0, int a1, int a2)
{
    if (a0 == 0) {
        *(int *)D_00232624 = 0;
        *(int *)D_00232628 = 0;
        *(int *)D_0023262C = 0;
    } else {
        *(int *)D_00232624 = a0;
        *(int *)D_00232628 = a1;
        *(int *)D_0023262C = a2;
    }
}
