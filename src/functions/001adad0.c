// FUNCTION: SLPM 0x001ADAD0  size 72  core 72
extern void FUN_001af7d0(void);
extern int FUN_001adb18(void *p, int v);
extern void FUN_001af7e8(void);

int FUN_001adad0(char *p, int v)
{
    int r;

    FUN_001af7d0();
    r = FUN_001adb18(p, v);
    FUN_001af7e8();
    return r;
}
