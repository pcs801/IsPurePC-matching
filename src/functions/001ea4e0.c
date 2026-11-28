// FUNCTION: SLPM 0x001EA4E0  size 96  core 68  (splat merged two functions)
// 0x1EA4E8 progress: words 0-2 now match the target exactly
//   (`addiu v1,a2,0x13` first, computed into a temp before the frame).
// Remaining diff: the target puts `addiu sp,-0x10` at word1 and `addiu a2,a2,0x22`
// after `sd ra`; ee-gcc hoists the a2 modify differently and the function ends 12
// bytes short (56 vs 68). Best shape so far - keep as the near-miss baseline.
extern void FUN_001e9ac0(int, int, int);

int FUN_001ea4e0(void)
{
    return 1;
}

void FUN_001ea4e8(char *p, int a1, int a2)
{
    int v;

    v = a2 + 0x13;
    a2 = a2 + 0x22;
    if (v > -1)
        a2 = v;
    FUN_001e9ac0(*(int *)(p + 0x40), a1, (a2 >> 4) << 4);
}
