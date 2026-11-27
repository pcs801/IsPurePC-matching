// FUNCTION: SLPM 0x00110518  size 128 (core 124)
// Ring-buffer writer: while the "full" flag is clear, take min(n, 40-have) into +0x2C and
// raise the flag once the buffer reaches 40; then advance +0x34 by n modulo +0x3C and add n
// to +0x38 / +0x40. Status: 128/124, 26 words off (shape still approximate).
int FUN_00110518(char *p, unsigned int n)
{
    int have;
    int room;
    unsigned int take;

    if (*(int *)p == 0) {
        have = *(int *)(p + 0x2C);
        room = 40 - have;
        take = n < (unsigned int)room ? n : (unsigned int)room;
        have += (int)take;
        n -= take;
        if ((unsigned int)have >= 40) {
            *(int *)(p + 0x2C) = have;
            *(int *)p = 1;
        }
    }
    *(int *)(p + 0x34) = (*(int *)(p + 0x34) + (int)n) % *(int *)(p + 0x3C);
    *(int *)(p + 0x38) = *(int *)(p + 0x38) + (int)n;
    *(int *)(p + 0x40) = *(int *)(p + 0x40) + (int)n;
    return 0;
}
