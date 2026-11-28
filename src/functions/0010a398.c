// FUNCTION: SLPM 0x0010A398  size 56  core 56
extern void FUN_0019ed10(void *a0, int a1);

void FUN_0010a398(int a0)
{
    int s[4];

    s[0] = 0;
    s[1] = 0;
    s[2] = 640;
    s[3] = 448;
    FUN_0019ed10(s, a0 & 0xFFFF);
}
