// FUNCTION: SLPM 0x001F8EB8  size 96  core 80
// b2 must be 64-bit so the two stores are `sd` (target ff a4 00 40 / ff a5 00 48)
extern void FUN_001fa998(int *, char *);
extern void FUN_001faa58(char *, char *);

void FUN_001f8eb8(int a0, int a1)
{
    char b1[0x20];
    char bs[0x20];
    long long b2[2];

    b2[0] = a0;
    b2[1] = a1;
    FUN_001fa998((int *)b2, b1);
    FUN_001fa998((int *)&b2[1], bs);
    FUN_001faa58(b1, bs);
}
