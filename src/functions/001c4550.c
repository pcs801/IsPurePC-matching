// FUNCTION: SLPM 0x001C4550  size 88  core 88
extern void FUN_001c46a0(void);
extern int FUN_001c4588(void *p);
extern void FUN_001c46a8(void);

int FUN_001c4550(char *p)
{
    int r;

    FUN_001c46a0();
    r = FUN_001c4588(p);
    FUN_001c46a8();
    return r;
}
