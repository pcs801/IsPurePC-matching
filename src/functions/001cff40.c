// FUNCTION: SLPM 0x001CFF40  size 48 (core 48)
// Early-out setter family: if p[3] != 0 return 0; else store the 5 fields and return 1.
// Status: 48/48 bytes, 9 words off (target schedules the p[5] constant into the bnez delay
// slot and keeps p[3] in v0; we get v1 / a different delay fill).
int FUN_001cff40(int *p, int a1, int a2, int a3, int a4)
{
    int r = 0;

    if (p[3] == 0) {
        p[9] = a4;
        p[6] = a1;
        p[7] = a2;
        p[5] = 2;
        p[8] = a3;
        r = 1;
    }
    return r;
}
