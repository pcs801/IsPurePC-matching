// FUNCTION: SLPM 0x0019BCC8  size 80 (core 80)
// Bounds-checked 16-bit pixel getter. The params must be UNSIGNED so gcc emits the
// bltz + sltu pair the target has (a plain int compare gives slt instead).
int FUN_0019bcc8(int *p, unsigned int x, unsigned int y)
{
    if ((int)x < 0 || x >= (unsigned int)p[0])
        return 1824;
    if ((int)y < 0 || y >= (unsigned int)p[1])
        return 1824;
    return *(unsigned short *)(p[2] + ((int)y * p[0] + (int)x) * 2);
}
