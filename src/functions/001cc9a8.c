// FUNCTION: SLPM 0x001CC9A8  size 56
extern void FUN_001fbb84(char *, int, int);

void FUN_001cc9a8(char *p)
{
    *(short *)(p + 0xE0) = 0;
    *(int *)(p + 0xCC) = 0;
    *(short *)(p + 0xE2) = -0x80;
    *(short *)(p + 0xE4) = -0x80;
    FUN_001fbb84(p + 0xD0, 0, 0x10);
}
