// FUNCTION: SLPM 0x001E2390  size 56  core 56
extern void FUN_001e1c68(void);

int FUN_001e2390(int *p, int a1)
{
    if (a1 == 1)
        return (*(unsigned int *)p >> 8) & 1;
    FUN_001e1c68();
    return 0;
}
