// FUNCTION: SLPM 0x00117760  size 40  core 40
// sig: lw ; lui ; addiu ; lw ; lw ; subu ; addiu ; sw ; jr ; sw

extern int *D_00270CAC;
extern char D_1B73FC0[];

void FUN_00117760(void) {
    int *p = D_00270CAC;
    char *q = D_1B73FC0;
    int d = *(int *)((char *)p + 0x52F4) - (int)p - 0x551C;
    *(int *)(q + 0xD4) = *(int *)((char *)p + 0x52E0);
    *(int *)(q + 0xD8) = d;
}
