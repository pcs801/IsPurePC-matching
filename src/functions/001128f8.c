// FUNCTION: SLPM 0x001128F8  size 64  core 64
extern char D_001B7E4F0[];
extern void FUN_00114348(void *a0, void *a1);

int FUN_001128f8(int a0, char *out)
{
    long long buf[4];

    FUN_00114348(D_001B7E4F0, buf);
    *(long long *)(out + 8) = buf[0];
    *(long long *)(out + 16) = buf[1];
    return 1;
}
