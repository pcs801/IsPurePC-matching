// FUNCTION: SLPM 0x001B70C8  size 48  core 48
// if (p == 0) { FUN_001cf618(D_0265EB0); return -1; } return *(signed char*)(p + 1);
extern void FUN_001cf618(char *);
extern char D_0265EB0[];

int FUN_001b70c8(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_0265EB0);
        return -1;
    }
    return *(signed char *)(p + 1);
}
