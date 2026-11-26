// FUNCTION: SLPM 0x00105CB0  size 216  core 216
// sig: addiu ; slti ; daddu ; movn ; sra ; sll ; lui ; addu ; lbu ; subu ; srav ; jr

extern unsigned char D_00A98DB9[];

int FUN_00105cb0(int a) {
    return (D_00A98DB9[a / 8] >> (a % 8)) & 1;
}

void FUN_00105ce8(void) {
}

int FUN_00105cf0(unsigned char *p, int b) {
    return (p[b / 8] >> (b % 8)) & 1;
}

void FUN_00105d20(unsigned char *p, int b, int v) {
    if (v == 0)
        p[b / 8] &= ~(1 << (b % 8));
    else
        p[b / 8] |= 1 << (b % 8);
}
