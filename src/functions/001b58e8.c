// FUNCTION: SLPM 0x001B58E8  size 64  core 64
extern int FUN_001b57c0(void *p);

int FUN_001b58e8(char *p, int *out)
{
    long long r = FUN_001b57c0(p);

    *out = (int)((r + 2047) / 2048);
    return 1;
}
