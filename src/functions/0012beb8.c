// FUNCTION: SLPM 0x0012beb8  size 96  core 92  -G8
extern int D_00270CAC;

void FUN_0012beb8(int idx)
{
    char *b = (char *)(D_00270CAC + idx * 264 + 0x3DEF8);
    int a = *(int *)(b + 0x40);
    int c = *(int *)(b + 0x44);

    a >>= 4;
    c >>= 4;
    *(int *)(b + 0x20) += a;
    *(int *)(b + 0x24) += c;
    *(int *)(b + 0x58) = a;
    *(int *)(b + 0x5C) = c;
    *(int *)(b + 0x40) = 0;
    *(int *)(b + 0x44) = 0;
}
