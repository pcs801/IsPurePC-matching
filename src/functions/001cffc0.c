// FUNCTION: SLPM 0x001CFFC0  size 40  core 36
extern int FUN_001fbb84(void *p, int c, int n);

void FUN_001cffc0(char *p)
{
    *(int *)(p + 12) = 0;
    FUN_001fbb84(p + 40, 0, 8);
}
