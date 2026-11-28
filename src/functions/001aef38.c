extern int FUN_001af7d0(int a0, int a1);
extern int FUN_001aef80(int a0, int a1);
extern int FUN_001af7e8(void);

int FUN_001aef38(int a0, int a1)
{
    int r;

    FUN_001af7d0(a0, a1);
    r = FUN_001aef80(a0, a1);
    FUN_001af7e8();
    return r;
}
