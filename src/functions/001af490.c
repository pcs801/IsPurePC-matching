extern int FUN_001af7d0(int a0, int a1);
extern int FUN_001af4d8(int a0, int a1);
extern int FUN_001af7e8(void);

int FUN_001af490(int a0, int a1)
{
    int r;

    FUN_001af7d0(a0, a1);
    r = FUN_001af4d8(a0, a1);
    FUN_001af7e8();
    return r;
}
