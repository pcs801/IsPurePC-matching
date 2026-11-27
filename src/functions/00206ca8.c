// FUNCTION: SLPM 0x00206CA8
void FUN_00206ca8(char *p)
{
    int a = *(int *)(p + 4);
    int i = *(int *)(p + 0xC);
    int n = *(int *)p;

    *(int *)(p + 4) = a + 1;
    i = i + 1;
    *(int *)(p + 0xC) = i;
    if (i == (int)(p + n + 0x10))
        *(int *)(p + 0xC) = (int)(p + 0x10);
}
