// FUNCTION: SLPM 0x00107910
extern int FUN_0010bd80(unsigned int cmd, void *arg);
extern unsigned char D_270E80[];
extern unsigned int D_456490[16];

void FUN_00107910(void)
{
    if (D_270E80[0x10682] != 0) {
        FUN_0010bd80(0xD1, (void *)0);
        D_456490[12] = FUN_0010bd80(0x8020, (void *)0);
        D_456490[13] = FUN_0010bd80(0x8161, (void *)0);
    }
    D_270E80[0x10682] = 0;
}
