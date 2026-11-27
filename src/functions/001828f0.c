// FUNCTION: SLPM 0x001828F0  size 36  (MISS 68/36)
// ROM: addiu sp,-0x40 ; sd s0,0x20 ; sd s1,0x28 ; sd ra,0x30 ; jal FUN_0017f298 (s1 = *(int*)(a0+0x44)) ;
//      bnel v0,zero,L (v0 = 0) ; jal ... ; (symbol ends without an epilogue)
// frame -0x40 with 3 saves means the real body is longer than the 36-byte symbol.

extern int FUN_0017f298(int a0);
extern int FUN_0019f0c8(int a0);

int FUN_001828f0(int a0)
{
    int s1;
    int r;

    s1 = *(int *)(a0 + 0x44);
    r = FUN_0017f298(a0);
    if (r != 0)
        return 0;
    return FUN_0019f0c8(s1);
}
