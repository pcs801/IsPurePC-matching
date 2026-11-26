// FUNCTION: SLPM 0x001058A8  size 72  core 72
// sig: blez ; andi ; lui ; lw ; addiu ; nop ; lw ; addiu ; addiu ; nop ; nop ; bnez

extern int D_00B1EC04;
extern unsigned char D_00A969D0[];

unsigned char FUN_001058a8(int n, int b) {
    int sum = b & 0xFFFF;
    int i;
    for (i = 0; i < n; i++)
        sum += *(int *)((char *)D_00B1EC04 + 16 + i * 20);
    return D_00A969D0[sum];
}
