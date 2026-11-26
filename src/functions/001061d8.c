extern unsigned char D_A98DA7;
extern char D_B264B0[];

void FUN_001061d8(int i, int v)
{
    if (D_A98DA7 == 0) {
        if (v) {
            D_B264B0[i * 6] = 1;
            D_B264B0[i * 6 + 1] = v;
        } else {
            D_B264B0[i * 6] = 0;
            D_B264B0[i * 6 + 1] = 0;
        }
    } else {
        D_B264B0[i * 6] = 0;
        D_B264B0[i * 6 + 1] = 0;
    }
}
