// FUNCTION: SLPM 0x001BF388  size 48  core 60
// the second FUN_001bf5a8 return value must live in $s0 (a local that outlives the call)
extern int FUN_001bf5a8(int);
extern void FUN_001f4e30(int);

int FUN_001bf388(void)
{
    int r;

    FUN_001bf5a8(0x2300);
    FUN_001f4e30(1);
    do {
        r = FUN_001bf5a8(0x2301);
    } while (0);
    return r;
}
