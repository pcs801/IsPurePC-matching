// FUNCTION: SLPM 0x002072B0  size 48  core 52
extern void FUN_002071c8(int);

void FUN_002072b0(int x)
{
    int y;

    if (x == 0xA) {
        FUN_002071c8(0xD);
        y = 0xA;
        FUN_002071c8(y);
        return;
    }
    FUN_002071c8(x);
}
