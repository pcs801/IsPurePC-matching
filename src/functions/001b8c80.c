// FUNCTION: SLPM 0x001B8C80  size 48  core 48
extern char D_002663B8[];
extern void FUN_001cf618(char *);

int FUN_001b8c80(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_002663B8);
        return 0;
    }
    return *(int *)(p + 0x14);
}
