// FUNCTION: SLPM 0x001B5860  size 56  core 56
// The symbol region (60 B) = this wrapper (44 B) + 4-byte nop + the small
// function at 0x001B5890 (stores to its 2nd arg, returns 1).
extern int FUN_001bd078(int v);

void FUN_001b5860(char *p, int *out)
{
    *out = FUN_001bd078(*(int *)(p + 8));
}

int FUN_001b5890(int a0, int *p)
{
    (void)a0;
    *p = 0;
    return 1;
}
