// FUNCTION: SLPM 0x001B8160  size 56  core 56
extern char D_00266140[];
extern char D_002304C4[];
extern void FUN_001cf618(void *a0);

void FUN_001b8160(char *p, int v)
{
    if (p == 0) {
        FUN_001cf618(D_00266140);
        return;
    }
    *(int *)(p + 56) = v;
    *(int *)D_002304C4 = v;
}
