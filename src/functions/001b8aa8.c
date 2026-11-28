// FUNCTION: SLPM 0x001B8AA8  size 48  core 48
extern char D_00266358[];
extern void FUN_001cf618(char *);

int FUN_001b8aa8(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_00266358);
        return -1;
    }
    return *(int *)(p + 0x4C);
}
