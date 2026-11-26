// FUNCTION: SLPM 0x00105C20  size 144  core 144
extern unsigned char D_00A98DB9[];

void FUN_00105c20(int a, int v)
{
    if (v == 0)
        D_00A98DB9[a / 8] &= ~(1 << (a % 8));
    else
        D_00A98DB9[a / 8] |= 1 << (a % 8);
}
