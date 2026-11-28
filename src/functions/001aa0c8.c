// FUNCTION: SLPM 0x001AA0C8  size 48
extern void FUN_001fc8c0(char *, int);

int FUN_001aa0c8(char *a0, int a1, int a2)
{
    if (a0 != 0)
        FUN_001fc8c0(a0, a2 * 4 + a1);
    return 0;
}
