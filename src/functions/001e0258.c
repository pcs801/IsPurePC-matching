// FUNCTION: SLPM 0x001E0258  size 128  core 124
int FUN_001e0258(int sel, int a, int b)
{
    int x = a & 0xFFFF;
    int y = b & 0xFFFF;

    switch (sel & 7) {
    case 0:
        return (x * y) >> 2;
    case 1:
        return ((x * y) >> 4) * 3;
    case 2:
        return (x * y) >> 3;
    case 3:
        return (x * y) >> 4;
    case 4:
        return (x * y) >> 5;
    }
    return 0;
}
