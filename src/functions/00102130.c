// FUNCTION: SLPM 0x00102130  size 96 (core 92)
extern int D_D6E680[4];

int FUN_00102130(int a0)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (D_D6E680[i] == 0) {
            D_D6E680[i] = a0;
            break;
        }
    }
    return i != 4 ? i : -1;
}
