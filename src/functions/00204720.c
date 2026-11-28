// FUNCTION: SLPM 0x00204720  size 48  core 44
// if ((*(u16*)(p+0xC) & 9) == 9) return FUN_002024f8(p); return 0;
extern int FUN_002024f8(char *);

int FUN_00204720(char *p)
{
    if ((*(unsigned short *)(p + 0xC) & 9) == 9)
        return FUN_002024f8(p);
    return 0;
}
