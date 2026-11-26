// FUNCTION: SLPM 0x00123940  size 40
// sig: lw ; lw ; sll ; addu ; sll ; subu ; sll ; addu ; jr ; sw

extern char *D_00270CB0;

void FUN_00123940(int p) {
    char *base = D_00270CB0;
    int n = *(int *)base;
    *(int *)(base + n * 0x5FF8 + 0x38) = p;
}
