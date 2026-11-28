// FUNCTION: SLPM 0x0019B5B0  size 48  core 52
extern void FUN_0019b058(int);

void FUN_0019b5b0(char *p)
{
    FUN_0019b058(*(int *)(p + 8));
    *(int *)(p + 8) = 0;
    ((int *)p)[1] = 0;
    *(int *)p = 0;
}
