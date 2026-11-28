extern char D_00270CC4[];
extern int FUN_002060a0(int a0);

void FUN_001fbe68(int *out, int a1)
{
    int v;

    *(int *)D_00270CC4 = 0;
    v = FUN_002060a0(a1);
    if (v == -1) {
        int w = *(int *)D_00270CC4;
        *out = w;
    }
}
