// FUNCTION: SLPM 0x002113c0  size 72  core 68
extern char D_872C88[];
extern int FUN_00205dd0(int a0, void *a1);

int FUN_002113c0(unsigned short a0, int a1, int a2)
{
    int buf[4];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = (int)D_872C88 | 0x20000000;
    return FUN_00205dd0(1, buf);
}
