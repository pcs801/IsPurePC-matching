// FUNCTION: SLPM 0x0017A870  size 136 (core 132)
// Luminance pass: for every 4-byte entry in [start,end) (offsets stored in the header
// at p+n*4-4 and p+n*4), replace all three colour bytes with
//   (r*1228 + g*2416 + b*450) >> 12
// Store order in the target is byte0, byte2, byte1.
void FUN_0017a870(char *p)
{
    int n = *(int *)p;
    int start = *(int *)(p + n * 4 - 4);
    int end = *(int *)(p + n * 4);
    unsigned char *q = (unsigned char *)(p + start);
    int count = (int)((unsigned int)(end - start) >> 2);
    int i;

    for (i = count; i != 0; i--, q += 4) {
        int g = (q[0] * 1228 + q[1] * 2416 + q[2] * 450) >> 12;

        q[0] = (char)g;
        q[2] = (char)g;
        q[1] = (char)g;
    }
}
