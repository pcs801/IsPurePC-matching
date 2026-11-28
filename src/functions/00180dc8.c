extern int FUN_0017f298(char *p);
extern void FUN_00180a68(int *q, int a1, int a2, int a3, int a4);

int FUN_00180dc8(char *p)
{
    int *q = *(int **)(p + 0x44);

    if (FUN_0017f298(p) == 0) {
        int v = *(int *)((char *)q + 0xC);

        FUN_00180a68(q, v, 0, 1, 1);
        return 0;
    }
    return 0;
}
