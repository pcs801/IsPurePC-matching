extern void FUN_001ae400(void);
extern void FUN_001af7d0(int *p, int b, int c);
extern int FUN_001ae558(int *p, int b, int c);
extern void FUN_001af7e8(void);

void FUN_001ae4e8(void)
{
    FUN_001ae400();
}

int FUN_001ae500(int *p, int b, int c)
{
    int r;

    FUN_001af7d0(p, b, c);
    r = FUN_001ae558(p, b, c);
    FUN_001af7e8();
    return r;
}
