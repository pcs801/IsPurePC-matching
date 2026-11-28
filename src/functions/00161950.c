extern char D_00217AF8[];
extern int FUN_0019daf8(char *a0, int a1, int a2, int a3);

int FUN_00161950(int a0, int a1, int a2)
{
    *(int *)(a0 + 8) = a1;
    *(int *)(a0 + 0xC) = a2;
    return FUN_0019daf8(D_00217AF8, a0, 1024, 2);
}
