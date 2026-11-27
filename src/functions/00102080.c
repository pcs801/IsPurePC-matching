// FUNCTION: SLPM 0x00102080  size 80
// note: the target reads the counter twice (lw v1 / lw v0) because the original
// source reached it through two declarators; D_00270C44[1] aliases D_00270C48.
extern int D_00270C44[2];
extern int D_00270C48;
extern int FUN_001dc7b8();

void FUN_00102080(void)
{
    int i;
    if (D_00270C44[1] == 1) return;
    for (i = 0; i < D_00270C48; i++)
        FUN_001dc7b8(0);
}
