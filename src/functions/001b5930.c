extern void FUN_001b5c70(void);
extern int FUN_001b5978(int *p, int v);
extern void FUN_001b5c88(void);

int FUN_001b5930(int *p, int v)
{
    int r;

    FUN_001b5c70();
    r = FUN_001b5978(p, v);
    FUN_001b5c88();
    return r;
}
