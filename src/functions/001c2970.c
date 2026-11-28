// FUNCTION: SLPM 0x001C2970  size 60  core 60
extern char D_00268090[];
extern void FUN_001c1dc8(void *a0, void *a1);

int FUN_001c2970(char *p)
{
    if (p == 0) {
        FUN_001c1dc8(p, D_00268090);
        return 0;
    }
    if (*(signed char *)(p + 2) == 1)
        return *(int *)(p + 40) << 11;
    return 0;
}
