extern void FUN_001af7d0(int *p, int b, int c);
extern int FUN_001aeb60(int *p, int b, int c);
extern void FUN_001af7e8(void);

int FUN_001aeb08(int *p, int b, int c)
{
    int r;

    FUN_001af7d0(p, b, c);
    r = FUN_001aeb60(p, b, c);
    FUN_001af7e8();
    return r;
}
