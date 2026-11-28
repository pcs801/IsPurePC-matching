// FUNCTION: SLPM 0x001ADEF8  size 72  core 72
extern void FUN_001af7d0(void);
extern int FUN_001adf40(void *p, int v);
extern void FUN_001af7e8(void);

int FUN_001adef8(char *p, int v)
{
    int r;

    FUN_001af7d0();
    r = FUN_001adf40(p, v);
    FUN_001af7e8();
    return r;
}
