// FUNCTION: SLPM 0x00104C10  size 408  core 404
// MISS: 392/404 bytes (12 bytes short) plus a callee-saved register shift
// (target: i in $s5, n in $s3, two copies of the base in $s7/$fp). Recovered shape:
//   * t = *(int **)(D_B1EC00 + 0x695C)   - entry-table pointer, table stride 8,
//     entry pointer at t[2*i + 1];
//   * slot count D_B1EC00+0x6B80 is re-read every outer iteration (unsigned compare);
//   * per-slot count byte at D_B1EC00 + 0x6B60 + i is re-read as the inner bound
//     (signed compare) and the address is built as (i + 0x6B60) + (int)base so that
//     ee-gcc emits addiu-then-addu;
//   * inner body: FUN_00105818(e[j]) == 1 skips, otherwise n += bit of D_A98D50 at
//     index e[j], mask written as e[j] - ((e[j] / 8) << 3) (gives subu, not andi);
//   * if (n) return 0; then mark D_A98D10 bits for every entry whose FUN_00105818(i)
//     equals 1, and return 1.
extern unsigned char D_B1EC00[];
extern unsigned char D_A98D50[];
extern unsigned char D_A98D10[];
extern unsigned short FUN_00105818(int i);

int FUN_00104c10(void)
{
    unsigned char *base = D_B1EC00;
    int *t = *(int **)(base + 0x695C);
    int i;
    int j;
    int n = 0;

    for (i = 0; i < *(unsigned int *)(base + 0x6B80); i++) {
        unsigned short *e;
        if (*(unsigned char *)((i + 0x6B60) + (int)base) == 0)
            continue;
        e = (unsigned short *)t[2 * i + 1];
        for (j = 0; j < *(unsigned char *)((i + 0x6B60) + (int)base); j++) {
            if (FUN_00105818(e[j]) == 1)
                continue;
            n += (D_A98D50[e[j] / 8] >> (e[j] - ((e[j] / 8) << 3))) & 1;
        }
    }
    if (n != 0)
        return 0;
    for (i = 0; i < *(unsigned int *)(base + 0x6958); i++) {
        if (FUN_00105818(i) != 1)
            continue;
        D_A98D10[i / 8] |= 1 << (i - ((i / 8) << 3));
    }
    return 1;
}
