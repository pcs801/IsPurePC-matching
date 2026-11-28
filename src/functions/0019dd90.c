void FUN_0019dd90(void)
{
    int *p = (int *)0x01BA0D40;
    int i;

    for (i = 255; i >= 0; i--) {
        *p = -1;
        p--;
    }
}
