// FUNCTION: SLPM 0x00208ab0  size 80  core 76
void FUN_00208ab0(int i)
{
    int *p;

    if (i < 0)
        p = (int *)(*(int *)0x0086CF64 + (i & 0x7FFFFFFF) * 12);
    else
        p = (int *)(*(int *)0x0086CF6C + i * 12);
    *p = 0;
}
