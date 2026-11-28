extern int FUN_0012d350(int a0);
extern int FUN_00117dc0(int a0, int a1);

int FUN_0011cf80(int a0)
{
    int q;

    if (FUN_0012d350(a0) == 0) {
        q = *(int *)(a0 + 0x44);
        *(int *)(q + 8) = *(int *)(q + 8) + 4;
        FUN_00117dc0(a0, *(int *)(q + 8));
    } else {
        *(char *)(a0 + 0xD) = 0;
    }
    return 0;
}
