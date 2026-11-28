extern int FUN_0012beb8(int a0);
extern int FUN_00117dc0(int a0, int a1);

int FUN_0011cb28(int a0)
{
    int q;

    q = *(int *)(a0 + 0x44);
    FUN_0012beb8(*(unsigned char *)(*(int *)(q + 8) + 1));
    q = *(int *)(a0 + 0x44);
    *(int *)(q + 8) = *(int *)(q + 8) + 4;
    FUN_00117dc0(a0, *(int *)(q + 8));
    return 0;
}
