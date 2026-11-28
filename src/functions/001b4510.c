extern void FUN_001b4af8(void);
extern void FUN_001b4768(char *p);
extern void FUN_001fbb84(char *p, int a1, int a2);

void FUN_001b4510(char *p)
{
    if (p != 0) {
        FUN_001b4af8();
        FUN_001b4768(p);
        *p = 0;
        FUN_001fbb84(p, 0, 104);
    }
}
