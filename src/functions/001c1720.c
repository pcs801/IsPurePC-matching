// FUNCTION: SLPM 0x001C1720  size 48  core 44
extern int FUN_001fc9d4(char *);

int FUN_001c1720(char *p)
{
    if (FUN_001fc9d4(p) != 0x11)
        return 0;
    return *(signed char *)(p + 8) == 0x2E;
}
