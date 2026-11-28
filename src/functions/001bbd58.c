extern void FUN_001d0268(int a0);
extern void FUN_001d0c70(int a0);
extern void FUN_001fbb84(char *p, int a1, int a2);

void FUN_001bbd58(char *p)
{
    if (p != 0) {
        if (*(int **)(p + 4) != 0) {
            FUN_001d0268(*(int *)(p + 4));
            *(int *)(p + 4) = 0;
        }
        if (*(int **)p != 0) {
            FUN_001d0c70(*(int *)p);
            *(int *)p = 0;
        }
        FUN_001fbb84(p, 0, 80);
    }
}
