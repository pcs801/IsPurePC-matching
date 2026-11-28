// FUNCTION: SLPM 0x001CCB00  size 72  core 72
extern void FUN_001cfec8(int a0);
extern void FUN_001fbb84(void *a0, int a1, int a2);

void FUN_001ccb00(char *p)
{
    int v;

    if (p == 0)
        return;
    v = *(int *)(p + 8);
    *(int *)(p + 8) = 0;
    FUN_001cfec8(v);
    FUN_001fbb84(p, 0, 260);
    *(short *)p = 0;
}
