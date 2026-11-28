// FUNCTION: SLPM 0x00181650  size 48  core 44
// NEAR-MISS 1 word: target uses plain `bne` (0x14400005), ee-gcc always emits the
// branch-likely form `bnel` (0x54400005). Same displacement and delay slot - only the
// opcode differs, so this likely needs -mno-branch-likely rather than a source change.
extern int FUN_0017f6e8(char *);
extern void FUN_00180fc8(int *, int);

int FUN_00181650(char *p)
{
    int *q;
    int r;

    q = *(int **)(p + 0x44);
    r = FUN_0017f6e8(p);
    if (r != 0)
        return 0;
    FUN_00180fc8(q, q[3]);
    return 0;
}
