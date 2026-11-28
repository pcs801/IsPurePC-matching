extern void FUN_001af7d0(int *p);
extern int FUN_001af428(int *p);
extern void FUN_001af7e8(void);

int FUN_001af3f0(int *p)
{
    int r;

    FUN_001af7d0(p);
    r = FUN_001af428(p);
    FUN_001af7e8();
    return r;
}
