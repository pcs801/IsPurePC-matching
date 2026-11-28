extern int D_00241B70;
extern char D_00241B78[];
extern void FUN_001fbb84(char *p, int a1, int a2);

void FUN_001cbc38(void)
{
    if (--D_00241B70 == 0)
        FUN_001fbb84(D_00241B78, 0, 768);
}
