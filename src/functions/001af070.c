// FUNCTION: SLPM 0x001AF070  size 48  core 48
extern char D_002657E0[];
extern void FUN_001cf618(char *);

int FUN_001af070(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_002657E0);
        return -3;
    }
    return *(signed char *)(p + 1);
}
