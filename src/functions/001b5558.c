extern void FUN_001b5c70(int *p, int b, int c);
extern int FUN_001b55b0(int *p, int b, int c);
extern void FUN_001b5c88(void);

int FUN_001b5558(int *p, int b, int c)
{
    int r;

    FUN_001b5c70(p, b, c);
    r = FUN_001b55b0(p, b, c);
    FUN_001b5c88();
    return r;
}
