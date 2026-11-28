extern void FUN_001d20a8(int v);
extern void FUN_001fbb84(char *p, int a1, int a2);

void FUN_001d0c70(char *p)
{
    int v = *(int *)(p + 0x1B0);

    if (v != 0) {
        FUN_001d20a8(v);
        *(int *)(p + 0x1B0) = 0;
    }
    FUN_001fbb84(p, 0, 2600);
}
