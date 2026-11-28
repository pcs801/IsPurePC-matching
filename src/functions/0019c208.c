extern char D_01B9F8F0[];
extern int FUN_0019c170(int a0, int a1, int a2);
extern int FUN_0019c270(int a0, int a1, int a2);

void FUN_0019c208(int a0, int a1, int a2)
{
    char *p;

    p = D_01B9F8F0;
    *(int *)(p + 0x10) = a1;
    *(int *)(p + 0x14) = a2;
    *(int *)(p) = a0;
    FUN_0019c170(a0, a1, a2);
    FUN_0019c270(0, 0, 0);
}
