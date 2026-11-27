// FUNCTION: SLPM 0x00206CE8
void FUN_00206ce8(char *p)
{
    int a = *(int *)(p + 4);
    int i = *(int *)(p + 8);
    int n = *(int *)p;

    *(int *)(p + 4) = a - 1;
    i = i + 1;
    *(int *)(p + 8) = i;
    if (i == (int)(p + n + 0x10))
        *(int *)(p + 8) = (int)(p + 0x10);
}
