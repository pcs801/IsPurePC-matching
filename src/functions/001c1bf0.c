// FUNCTION: SLPM 0x001C1BF0  size 32  core 32
// sig: lui ; lui ; addiu ; sw ; sb ; sb ; jr ; sb

extern char D_00231F30[];
extern int D_00231F34;

void FUN_001c1bf0(int a0, int a1, int a2, int a3)
{
    char *p = D_00231F30;
    D_00231F34 = a3;
    p[0] = a0;
    p[1] = a1;
    p[2] = a2;
}
