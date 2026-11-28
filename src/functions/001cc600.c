// FUNCTION: SLPM 0x001CC600
extern int D_00241EA0;
extern int D_00241EA4;

int FUN_001cc600(int a0)
{
    if (D_00241EA0 != 0)
        ((void (*)(int, int))D_00241EA0)(D_00241EA4, a0);
    return 0;
}
