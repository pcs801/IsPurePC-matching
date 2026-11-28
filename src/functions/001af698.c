// FUNCTION: SLPM 0x001AF698  size 48  core 44
// do-while keeps the real jal for the second call (a bare assignment becomes a sibcall)
extern void FUN_001af7d0(int);
extern int FUN_001af6d0(int);
extern int FUN_001af7e8(int);

int FUN_001af698(int a0)
{
    int r;

    FUN_001af7d0(a0);
    r = FUN_001af6d0(a0);
    do {
        r = FUN_001af7e8(r);
    } while (0);
    return r;
}
