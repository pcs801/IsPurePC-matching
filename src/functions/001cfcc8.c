extern int FUN_001b1190(void);

int FUN_001cfcc8(int a0)
{
    if (a0 == -1)
        a0 = FUN_001b1190() != 1 ? 1 : 2;
    return a0;
}
