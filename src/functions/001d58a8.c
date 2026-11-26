// FUNCTION: SLPM 0x001D58A8  size 48
extern int D_00246C70[];
extern char D_00246C78[];

int FUN_001d58a8(int idx, int **out) {
    *out = (int *)(D_00246C78 + idx * 0x3000);
    return D_00246C70[idx];
}
