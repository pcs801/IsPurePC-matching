// FUNCTION: SLPM 0x001282F8  size 48  (MISS 16/44)
// ROM: v1=*(gp-0x6ED8) ; v1=*(signed char*)(v1+4) ; beqz -> ret0 ; bltz -> ret1 ; slti 4 ; bnez -> ret1 ; ret1
// Every non-zero path returns 1, so a plain `return c != 0;` is 16 bytes vs the ROM's 44 -
// the ROM's redundant branches cannot come from a folded C condition (suspect
// a symbol-boundary / hand-written artifact). Needs a deeper look before retrying.

extern char *D_00270BE0;

int FUN_001282f8(void)
{
    return *(signed char *)(D_00270BE0 + 4) != 0;
}
