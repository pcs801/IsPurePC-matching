// FUNCTION: SLPM 0x001C0CF8  size 60  core 60
extern char D_00267B88[];
extern void FUN_001c0340(void *a0, void *a1);

int FUN_001c0cf8(char *p)
{
    if (p == 0) {
        FUN_001c0340(p, D_00267B88);
        return 0;
    }
    if (*(signed char *)(p + 2) == 1)
        return *(int *)(p + 20) << 11;
    return 0;
}
