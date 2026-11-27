// FUNCTION: SLPM 0x00111810  size 96  core 92
int FUN_00111810(char *a0, void *a1)
{
    int v = *(int *)(a0 + 0x50004);
    int n;

    if (v != 0) {
        n = *(int *)(a0 + 0x50000) - v + *(int *)(a0 + 0x50008);
        *(int *)a1 = (int)(a0 + n % *(int *)(a0 + 0x50008));
    }
    return v;
}
