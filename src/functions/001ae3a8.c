// FUNCTION: SLPM 0x001AE3A8  size 88  core 88
extern void FUN_001af7d0(void);
extern int FUN_001ae400(void *p, int v, int w);
extern void FUN_001af7e8(void);

int FUN_001ae3a8(char *p, int v, int w)
{
    int r;

    FUN_001af7d0();
    r = FUN_001ae400(p, v, w);
    FUN_001af7e8();
    return r;
}
