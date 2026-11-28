// FUNCTION: SLPM 0x001c88f8  size 72  core 68
extern char D_00269200[];
extern char D_002691B0[];
extern int FUN_001c8528(char *a0, char *a1);

void FUN_001c88f8(char *p, int a1, int a2, int a3)
{
    if (p == 0 || a1 == 0) {
        FUN_001c8528(D_00269200, D_002691B0);
        return;
    }
    *(int *)(p + 0x1C) = a1;
    *(int *)(p + 0x20) = a2;
    *(int *)(p + 0x24) = a3;
}
