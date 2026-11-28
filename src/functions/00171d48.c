// FUNCTION: SLPM 0x00171D48  size 80  core 80
extern char D_00218FE0[];
extern void FUN_0016f438(void *p, int a1, void *a2, int a3);
extern void FUN_0016eab0(void *p, int a1, int a2);

void FUN_00171d48(char *p, int a1, void *a2, int a3)
{
    int v = a3 & 0xFFFF;
    void *ap = a2;

    if (ap == 0)
        ap = D_00218FE0;
    FUN_0016f438(p, a1, ap, v);
    FUN_0016eab0(p, 1, v);
}
