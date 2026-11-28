// FUNCTION: SLPM 0x001ADBC0  size 56  core 56
extern void FUN_001af7d0(void);
extern int FUN_001adbf8(void *p);
extern void FUN_001af7e8(void);

int FUN_001adbc0(char *p)
{
    int r;

    FUN_001af7d0();
    r = FUN_001adbf8(p);
    FUN_001af7e8();
    return r;
}
