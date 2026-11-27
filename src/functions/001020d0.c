extern int D_D6E680[4];
int FUN_001020d0(void)
{
    int i;
    int r = 0;
    int *p = D_D6E680;
    for (i = 3; i >= 0; i--, p++) {
        int (*f)(void) = (int (*)(void))*p;
        if (f != 0) {
            f();
            *p = 0;
            r = 1;
        }
    }
    return r;
}
