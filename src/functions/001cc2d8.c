// FUNCTION: SLPM 0x001CC2D8  size 48  core 48
// six 8-byte accessors share this symbol range (splat merged them):
//   0x1CC2D8 sw +0x20 / 0x1CC2E0 lw +0x20 / 0x1CC2E8 swc1 +0x24 / 0x1CC2F0 lwc1 +0x24
//   0x1CC2F8 swc1 +0x28 / 0x1CC300 lwc1 +0x28
void FUN_001cc2d8(char *p, int v)
{
    *(int *)(p + 0x20) = v;
}

int FUN_001cc2e0(char *p)
{
    return *(int *)(p + 0x20);
}

void FUN_001cc2e8(char *p, float f)
{
    *(float *)(p + 0x24) = f;
}

float FUN_001cc2f0(char *p)
{
    return *(float *)(p + 0x24);
}

void FUN_001cc2f8(char *p, float f)
{
    *(float *)(p + 0x28) = f;
}

float FUN_001cc300(char *p)
{
    return *(float *)(p + 0x28);
}
