// FUNCTION: SLPM 0x001C43C8  size 64  core 60
extern void FUN_001c46a0(char *, int);
extern int FUN_001c4410(char *, int);
extern void FUN_001c46a8(void);

int FUN_001c43c8(char *a0, int a1)
{
    int r;

    FUN_001c46a0(a0, a1);
    r = FUN_001c4410(a0, a1);
    FUN_001c46a8();
    return r;
}
