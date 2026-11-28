// FUNCTION: SLPM 0x00210530  size 80  core 80
extern int D_00257688[];

int FUN_00210530(int *a0, int *a1)
{
    if (D_00257688[2] < 0)
        return 0x80008001;
    if (a0 != 0)
        *a0 = D_00257688[4];
    if (a1 != 0)
        *a1 = 0x80 - D_00257688[4];
    return 0;
}
