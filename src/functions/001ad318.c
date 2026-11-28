extern int FUN_001af7d0(int a0);
extern int FUN_001ad350(int a0);
extern int FUN_001af7e8(void);

int FUN_001ad318(int a0)
{
    int r;

    FUN_001af7d0(a0);
    r = FUN_001ad350(a0);
    FUN_001af7e8();
    return r;
}
