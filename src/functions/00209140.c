// FUNCTION: SLPM 0x00209140  size 48  (MISS 48/48, 6 words)
// ROM: a1=*(int*)(a0+0x24) ; v1=*(int*)(a0+0x18) ; div a1,v1 ; beql/break ; a1=*(int*)(a0+0x14) ;
//      mfhi v0 ; v1=v0+1 ; v0<<=6 ; *(int*)(a0+0x24)=v1 ; jr ra ; v0=a1+v0
// ee-gcc puts the divisor in v0 instead of v1 (RA difference); length and structure match.

int FUN_00209140(int self)
{
    int r;

    r = *(int *)(self + 0x24) % *(int *)(self + 0x18);
    *(int *)(self + 0x24) = r + 1;
    return *(int *)(self + 0x14) + (r << 6);
}
