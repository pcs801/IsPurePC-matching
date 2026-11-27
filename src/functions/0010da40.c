// FUNCTION: SLPM 0x0010DA40  size 48  core 44
// 2 words short of a match: the original epilogue is "sw $2,G1; sw $3,G2; jr $ra; nop"
// while ee-gcc 2.96 -O2 always schedules "sw $2,G1; move $2,$0; jr $ra; sw $3,G2"
// for this return-0 shape (and "sw; jr; sw" for the void shape).
extern int D_00270C70;
extern int D_00270C18;

int FUN_0010da40(int a0)
{
    int v0;
    int v1;

    if (a0 == 0) {
        v0 = 0x100;
        v1 = 0xDC;
    } else {
        v0 = 0x200;
        v1 = 0x1B8;
    }
    D_00270C70 = v0;
    D_00270C18 = v1;
    return 0;
}
