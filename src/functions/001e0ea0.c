void FUN_001e0ea0(char *p, int i, long long a, long long b)
{
    char *q = p + i * 16;

    *(long long *)(q + 40) = a;
    *(long long *)(q + 32) = b;
}
