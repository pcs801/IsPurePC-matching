// FUNCTION: SLPM 0x00112A70  size 72  core 68

void FUN_00112a70(int *p, int a, int *q, int n)
{
    p[3] = 0;
    p[0] = a;
    p[2] = 0;
    p[1] = (int)q;
    p[4] = n;
    if (n > 0) {
        do {
            *q = 0;
            q = (int *)((char *)q + 0x4CE40);
        } while (--n);
    }
}
