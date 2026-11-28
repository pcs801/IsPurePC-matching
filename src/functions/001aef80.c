// FUNCTION: SLPM 0x001AEF80  size 64  core 60
// if (a0 == 0) { FUN_001cf618(D_0265780); *a1 = 0; return -3; }
// *a1 = *(int*)(a0+0x14); return *(int*)(a0+0x18);
extern char D_0265780[];
extern void FUN_001cf618(char *);

int FUN_001aef80(char *a0, int *a1)
{
    if (a0 == 0) {
        FUN_001cf618(D_0265780);
        *a1 = 0;
        return -3;
    }
    *a1 = *(int *)(a0 + 0x14);
    return *(int *)(a0 + 0x18);
}
