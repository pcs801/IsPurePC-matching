// FUNCTION: SLPM 0x00211430  size 48  core 48
// sll/sra 24 on a1 = the parameter is sign-extended at entry -> plain `char` param
extern void FUN_00205dd0(int, void *);

void FUN_00211430(int a, char c)
{
    int buf[2];

    buf[0] = a;
    buf[1] = c;
    FUN_00205dd0(3, buf);
}
