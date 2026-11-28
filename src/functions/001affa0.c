extern int FUN_001ce9b8(void);
extern int FUN_001affd0(int a0);
extern int FUN_001ce9c0(void);

void FUN_001affa0(int a0)
{
    int s0;

    s0 = a0;
    do {
        FUN_001ce9b8();
        FUN_001affd0(s0);
    } while (0);
    FUN_001ce9c0();
}
