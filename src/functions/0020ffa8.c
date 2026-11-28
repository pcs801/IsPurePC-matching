extern int D_002576A0;

void FUN_0020ffa8(int *p)
{
    if (p[1])
        *(int *)p[1] = p[0];
    else
        D_002576A0 = p[0];
    if (p[0])
        *(int *)(p[0] + 4) = p[1];
    p[1] = 0;
}
