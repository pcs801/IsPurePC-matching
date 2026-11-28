// FUNCTION: SLPM 0x001AC488  size 96  core 96
extern int D_002241B8;
extern char D_00265068[];
extern int FUN_002059a0(void *param);

int FUN_001ac488(void)
{
    int buf[8];

    if (D_002241B8 >= 0)
        return D_002241B8;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = (int)D_00265068;
    D_002241B8 = FUN_002059a0(buf);
    if (D_002241B8 < 0)
        return -1;
    return D_002241B8;
}
