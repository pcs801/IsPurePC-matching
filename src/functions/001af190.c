// FUNCTION: SLPM 0x001AF190  size 48  core 44
// 7 args through a0..a3 + t0..t2: FUN_001af250(a0, a1, a2, sp, a3, t0, sp+4)
extern void FUN_001af250(int, int, int, void *, int, int, void *);

void FUN_001af190(int a0, int a1, int a2, int a3, int a4)
{
    char buf[16];

    FUN_001af250(a0, a1, a2, buf, a3, a4, buf + 4);
}
