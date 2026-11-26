// FUNCTION: SLPM 0x00107800
extern void FUN_00107910(void);
extern void FUN_00106268(void);
extern int FUN_0010bd80(unsigned int cmd, void *arg);
extern int FUN_00107990(int code);
extern unsigned char D_00281502;
extern unsigned int D_456490[16];

int FUN_00107800(void)
{
    FUN_00107910();
    D_00281502 = 1;
    FUN_00106268();
    D_456490[8] = FUN_0010bd80(0x8040, (void *)0);
    D_456490[9] = FUN_0010bd80(0x8030, (void *)0);
    D_456490[10] = FUN_0010bd80(0x8010, (void *)0);
    return FUN_00107990(-1);
}
