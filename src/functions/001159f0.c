// FUNCTION: SLPM 0x001159F0  size 304 (core 300)
// MISS: 328/300 bytes. Semantics recovered: bit-prefix counter over slot runs.
//   * switch (mode) 0..3 picks one of four 0x100-byte bit maps
//     (D_A94750 / D_A96750 / D_A96850 / D_A96950); default calls
//     FUN_0010bf68(D_00259638) and falls through with mode = 0.
//   * n = *(int *)(D_B1EC00 + 0x50); runs cursor = *(int *)(D_B1EC00 + 4) + mode*4,
//     stride 0x14; types = *(unsigned short **)(D_B1EC00 + 0x68A8) (0xFFFF = skip).
//   * for each of n entries: end = pos + runs[0]; if (*types != 0xFFFF) sum the bits
//     of the map for indices pos..end-1; pos = end; runs += 5; types++.
// Remaining gap: ee-gcc keeps mode in $a1 (copy at entry) and parks sum/pos/pointers
// in $s0-$s2 (frame 0x20 instead of 0x10) where the target keeps them in $t1/$t2/$t3/
// $t0/$t5 with no saved registers at all.
extern char D_B1EC00[];
extern char D_A96750[];
extern char D_A96850[];
extern char D_A96950[];
extern char D_A94750[];
extern char D_00259638[];
extern int FUN_0010bf68(int p);

int FUN_001159f0(int mode)
{
    char *base = D_B1EC00;
    unsigned char *bits;
    int i;
    int j;
    int sum = 0;
    int pos = 0;
    int n;
    int *runs;
    unsigned short *types;

    switch (mode) {
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
        FUN_0010bf68((int)D_00259638);
        mode = 0;
        bits = (unsigned char *)D_A94750;
        break;
    }
    n = *(int *)(base + 0x50);
    runs = (int *)(*(int *)(base + 4) + mode * 4);
    types = *(unsigned short **)(base + 0x68A8);
    for (i = 0; i < (unsigned int)n; i++) {
        int end = pos + runs[0];
        if (*types != 0xFFFF) {
            for (j = pos; j < end; j++)
                sum += (bits[j / 8] >> (j % 8)) & 1;
        }
        pos = end;
        runs += 5;
        types++;
    }
    return sum;
}
