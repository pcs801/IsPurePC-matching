// FUNCTION: SLPM 0x001D3D08  size 40 (core 40)
// Branch on *(s16*)(p+0x9C) == 1, both arms are tail calls.
extern void FUN_001d3b88(char *p);
extern void FUN_001d39d0(char *p);

void FUN_001d3d08(char *p)
{
    if (*(short *)(p + 0x9C) == 1)
        FUN_001d3b88(p);
    else
        FUN_001d39d0(p);
}
