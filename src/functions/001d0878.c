// FUNCTION: SLPM 0x001D0878
extern int D_00243C7C;
extern int D_00243C80;

int FUN_001d0878(int a0)
{
    if (D_00243C7C != 0)
        ((void (*)(int, int))D_00243C7C)(D_00243C80, a0);
    return 0;
}
