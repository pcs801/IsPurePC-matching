extern int FUN_001fbb84(int a0, int a1, int a2);

void FUN_001cfec8(int p)
{
    if (p != 0) {
        *(int *)p = 0;
        FUN_001fbb84(p, 0, 60);
    }
}

void FUN_001cff00(int a0, int a1)
{
    *(int *)(a0 + 8) = a1;
}
