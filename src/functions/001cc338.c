// FUNCTION: SLPM 0x001CC338  size 32  core 32
// v0 = 0x600 / sw a1,0xc4(a0) / div zero,a1,v0 / beql v0,zero,L / break 0,7 / mflo v1 / jr ra / sw v1,0xc8(a0)
void FUN_001cc338(char *p, int v)
{
    *(int *)(p + 0xC4) = v;
    *(int *)(p + 0xC8) = v / 0x600;
}
