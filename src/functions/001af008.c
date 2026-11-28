// FUNCTION: SLPM 0x001AF008  size 48  (MISS 56/48, 12 words)
// ROM: addiu sp ; bne a0,zero,L1 ; sd ra ; a0=0x2657B0 ; jal FUN_001cf618 ; v0=-3 ;
//      L1: v0=*(int*)(a0+0x1C) ; ld ra ; jr ra ; addiu sp
// ee-gcc emits an extra `daddu v0,a0,zero` and a duplicated epilogue (56 vs 48).

extern int FUN_001cf618(char *p);

int FUN_001af008(int a0)
{
    int r;

    if (a0 != 0) {
        r = *(int *)(a0 + 0x1C);
    } else {
        FUN_001cf618((char *)0x2657B0);
        r = -3;
    }
    return r;
}
