extern int FUN_00131ac0(int a0, int a1, int a2);
extern int FUN_00117dc0(int a0, int a1);

int FUN_0011d950(int a0)
{
    int q;

    FUN_00131ac0(*(int *)(*(int *)(a0 + 0x44) + 0xC),
                 *(int *)(*(int *)(*(int *)(a0 + 0x44) + 8) + 4),
                 *(unsigned short *)(*(int *)(*(int *)(a0 + 0x44) + 8) + 2));
    q = *(int *)(a0 + 0x44);
    *(int *)(q + 8) = *(int *)(q + 8) + 8;
    FUN_00117dc0(a0, *(int *)(q + 8));
    return 0;
}