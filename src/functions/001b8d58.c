// FUNCTION: SLPM 0x001B8D58  size 48  core 48
extern char D_00266420[];
extern void FUN_001cf618(char *);

int FUN_001b8d58(char *p)
{
    if (p == 0) {
        FUN_001cf618(D_00266420);
        return -1;
    }
    return *(signed char *)(p + 0x71);
}
