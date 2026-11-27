// FUNCTION: SLPM 0x00117088  size 224 (core 224)
// MISS: 232/224 bytes, first diff word 4 (andi destination register).
// Semantics recovered: masked bit test over a run of 32-bit words.
//   * switch (idx) 0..3 picks one of four bit maps; default calls
//     FUN_0010bf68(D_00259650) and returns 0.
//   * acc = (unsigned short)m truncated by the ABI (andi 0xFFFF), then acc &= 0xFFF;
//     if (n > 0) walk n 32-bit words from *(int *)(D_B1EC04) + idx*4 with stride 0x14
//     accumulating into acc.
//   * return (bits[acc >> 3] >> (acc & 7)) & 1   (unsigned acc => srl/andi).
// Remaining gap: ee-gcc puts the ABI truncation into $a2 (the parameter register)
// instead of $v1, so the whole register map shifts; 26 words differ.
extern char D_A94750[];
extern char D_A96750[];
extern char D_A96850[];
extern char D_A96950[];
extern char D_00259650[];
extern int D_B1EC04;
extern int FUN_0010bf68(int p);

int FUN_00117088(int idx, int n, unsigned short m)
{
    unsigned char *bits;
    unsigned int v = m;
    unsigned int acc;
    int *p;

    switch (idx) {
    case 0:
        bits = (unsigned char *)D_A94750;
        break;
    case 1:
        bits = (unsigned char *)D_A96750;
        break;
    case 2:
        bits = (unsigned char *)D_A96850;
        break;
    case 3:
        bits = (unsigned char *)D_A96950;
        break;
    default:
        FUN_0010bf68((int)D_00259650);
        return 0;
    }
    if (n > 0) {
        p = (int *)(D_B1EC04 + idx * 4);
        acc = v & 0xFFF;
        do {
            acc += *p;
            p = (int *)((char *)p + 20);
            n--;
        } while (n);
    }
    return (bits[acc >> 3] >> (acc & 7)) & 1;
}
