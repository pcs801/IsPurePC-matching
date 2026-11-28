// FUNCTION: SLPM 0x001C4CF8  size 48 core 44
extern int D_00236E5C;
extern int D_00236E60;

void FUN_001c4cf8(int a0)
{
    if (D_00236E5C != 0)
        ((void (*)(int))D_00236E5C)(D_00236E60);
}
