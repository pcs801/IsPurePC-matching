// FUNCTION: SLPM 0x0010DA40  size 48  core 44
extern int D_00270C70;
extern int D_00270C18;

void FUN_0010da40(int a0)
{
    int v0;
    int v1;

    if (a0) {
        v0 = 0x200;
        v1 = 0x1B8;
    } else {
        v0 = 0x100;
        v1 = 0xDC;
    }
    D_00270C70 = v0;
    D_00270C18 = v1;
}
