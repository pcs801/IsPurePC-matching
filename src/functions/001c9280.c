int FUN_001c9280(int *p)
{
    return p[9];
}

static void set_001c9288(int *p, int a, int b, int c)
{
    int i = a * 2 + b;
    ((int *)p)[i + 10] = c;
}

static int get_001c92a0(int *p, int a, int b, int c)
{
    int i = a * 2 + b;
    return ((int *)p)[i + 10];
}
