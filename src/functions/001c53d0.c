// FUNCTION: SLPM 0x001C53D0  size 56  core 56
extern char D_00268900[];
extern void FUN_001c4cf8(void *a0, void *a1);

int FUN_001c53d0(char *p)
{
    if (p == 0) {
        FUN_001c4cf8(p, D_00268900);
        return 0;
    }
    return *(int *)(p + 4);
}
