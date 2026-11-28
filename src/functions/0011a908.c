extern int FUN_001235a8(int a0, int a1);
extern int FUN_00117dc0(int a0, int a1);

int FUN_0011a908(int a0)
{
    int q;

    FUN_001235a8(*(int *)(*(int *)(a0 + 0x44) + 0xC) + *(int *)(*(int *)(*(int *)(a0 + 0x44) + 8) + 4),
                 *(unsigned char *)(*(int *)(*(int *)(a0 + 0x44) + 8) + 1));
    q = *(int *)(a0 + 0x44);
    *(int *)(q + 8) = *(int *)(q + 8) + 8;
    FUN_00117dc0(a0, *(int *)(q + 8));
    return 0;
}