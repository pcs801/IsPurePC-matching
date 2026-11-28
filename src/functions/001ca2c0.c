extern int FUN_001ca1b0(int a0);

void FUN_001ca2c0(char *p, int *out)
{
    out[0] = (int)(p + 16);
    out[1] = FUN_001ca1b0((int)(p + 8));
}
