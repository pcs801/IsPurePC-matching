// FUNCTION: SLPM 0x00181C08  size 48  core 44
// NEAR-MISS 1 word: target uses plain `bne` (0x14400005), ee-gcc always emits the
// branch-likely form `bnel` (0x54400005). Same displacement and delay slot - only the
// opcode differs, so this likely needs -mno-branch-likely rather than a source change.
extern int FUN_0017f298(char *);
extern void FUN_001817a0(int *, int);

int FUN_00181c08(char *p)
{
    int *q;
    int r;

    q = *(int **)(p + 0x44);
    r = FUN_0017f298(p);
    if (r != 0)
        return 0;
    FUN_001817a0(q, q[3]);
    return 0;
}
