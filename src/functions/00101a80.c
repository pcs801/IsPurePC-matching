// FUNCTION: SLPM 0x00101A80  size 40  (MISS 12/40)
// ROM: bgez a0,L ; lui a1,0x1B7 ; v0=a1+0x4230 ; a0=*(int*)(v0+8) ; L: v1=364 ; v0=a1+0x4230 ;
//      mult a0,v1 ; v1=v1+v0 ; jr ra ; v0=*(int*)(v1+0x13BC)
// The `mult` result is never consumed inside the 40-byte symbol (no mflo) and `v1 = 364 + base`
// ignores the product, so the recorded symbol is most likely truncated / mid-function.

extern char D_1B74230[];

int FUN_00101a80(int a0)
{
    if (a0 < 0)
        a0 = *(int *)(D_1B74230 + 8);
    return *(int *)(D_1B74230 + 364 + 0x13BC);
}
