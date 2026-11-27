// FUNCTION: SLPM 0x001E38B0  size 80 (core 80)
// Same predicate as 0x0019BCC8 but laid out ok-first in the target; best form found is
// the fail-first unsigned one (80/80, 10 words off on the branch layout).
int FUN_001e38b0(int *p, unsigned int x, unsigned int y)
{
    if ((int)x < 0 || x >= (unsigned int)p[0])
        return 1824;
    if ((int)y < 0 || y >= (unsigned int)p[1])
        return 1824;
    return *(unsigned short *)(p[2] + ((int)y * p[0] + (int)x) * 2);
}
