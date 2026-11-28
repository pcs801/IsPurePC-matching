// FUNCTION: SLPM 0x001176F8  size 72  core 64
extern char *D_00270CAC;
extern void FUN_0011fcd8(void);
extern void FUN_00125a18(int, int);

void FUN_001176f8(void)
{
    if (*(unsigned char *)(D_00270CAC + 0x47B) != 0) {
        FUN_0011fcd8();
    }
    *(unsigned char *)(D_00270CAC + 0x47B) = 0;
    FUN_00125a18(2, 0);
}
