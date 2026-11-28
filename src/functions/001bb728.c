// FUNCTION: SLPM 0x001bb728  size 112  core 108
// ROM: guard chain + two tail-call blocks (L778 out-of-line). Closest form found:
// nested-if keeps a single fallthrough tail call; 19 words off.
extern int FUN_001b5be8(int a0);

int FUN_001bb728(char *p)
{
    int v;

    if (p == 0)
        return 0;
    v = *(int *)(p + 8);
    if (v == 0) {
        v = *(int *)(p + 0x94);
        if (v == 0)
            return 0;
        v = *(int *)(v + 0x28);
        if (v == 0)
            return 0;
        return FUN_001b5be8(v);
    }
    return FUN_001b5be8(v);
}
