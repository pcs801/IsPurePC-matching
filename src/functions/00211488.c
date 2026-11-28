// FUNCTION: SLPM 0x00211488  size 48  core 48
// frame 0x30 with ra at 0x20 -> 32 bytes of locals: int buf[8] (only 3 slots used)
extern void FUN_00205dd0(int, void *);

void FUN_00211488(unsigned char a, int b, int c)
{
    int buf[8];

    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    FUN_00205dd0(0x20, buf);
}
