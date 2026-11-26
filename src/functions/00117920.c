// FUNCTION: SLPM 0x00117920  size 88  core 88
// sig: addiu ; lui ; sd ; addiu ; lbu ; andi ; andi ; beqz ; addiu ; lw ; sw ; lbu

extern char D_A94700[];
extern int *D_00270CAC;
extern void FUN_00106668(int);

void FUN_00117920(void) {
    char *p = D_A94700;
    unsigned char v = *(unsigned char *)(p + 0x46A2);
    unsigned char f = v & 1;
    unsigned char g;
    if (f) {
        D_00270CAC[291] = 30;
        v = *(unsigned char *)(p + 0x46A2);
    }
    g = (v >> 1) & 1;
    if (g)
        FUN_00106668(11);
}
