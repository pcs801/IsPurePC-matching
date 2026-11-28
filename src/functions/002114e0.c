// FUNCTION: SLPM 0x002114E0  size 48  core 52
extern void FUN_00205dd0(int, void *);

void FUN_002114e0(int a0, int a1, int a2)
{
    int buf[4];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = (unsigned short)a2;
    FUN_00205dd0(-5, buf);
}
