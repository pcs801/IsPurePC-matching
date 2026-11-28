extern int FUN_001c46a0(void);
extern int FUN_001c3a80(int a0);
extern int FUN_001c46a8(void);

void FUN_001c3a50(int a0)
{
    int s0;

    s0 = a0;
    do {
        FUN_001c46a0();
        FUN_001c3a80(s0);
    } while (0);
    FUN_001c46a8();
}
