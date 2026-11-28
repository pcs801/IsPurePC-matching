extern int FUN_001af7d0(int a0, int a1, int a2, int a3);
extern int FUN_001acc18(int a0, int a1, int a2, int a3);
extern int FUN_001af7e8(void);

int FUN_001acbb0(int a0, int a1, int a2, int a3)
{
    int r;

    FUN_001af7d0(a0, a1, a2, a3);
    FUN_001acc18(a0, a1, a2, a3);
    do {
        r = FUN_001af7e8();
    } while (0);
    return r;
}
