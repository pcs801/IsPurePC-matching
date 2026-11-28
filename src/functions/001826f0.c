// ROM: bne v0,zero,L (plain branch, delay v0=0) ; ee-gcc emits bnel instead (1 word).

extern int FUN_0017f6e8(int a0);
extern int FUN_00182498(int a0, int a1);

int FUN_001826f0(int a0)
{
    int s0;
    int r;

    s0 = *(int *)(a0 + 0x44);
    r = FUN_0017f6e8(a0);
    if (r != 0)
        return 0;
    FUN_00182498(s0, *(int *)(s0 + 0xC));
    return 0;
}
