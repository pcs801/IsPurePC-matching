extern void FUN_001c3ea0(char *p);
extern void FUN_001fbb84(char *p, int a1, int a2);

void FUN_001c3a80(char *p)
{
    if (p != 0) {
        FUN_001c3ea0(p);
        *p = 0;
        FUN_001fbb84(p, 0, 568);
    }
}
