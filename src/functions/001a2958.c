// FUNCTION: SLPM 0x001A2958  size 96  core 92
// int b[4]; b[i] = p[i] << 4; FUN_001a1f98(b);
extern void FUN_001a1f98(int *);

void FUN_001a2958(int *p)
{
    int b[4];

    b[0] = p[0] << 4;
    b[1] = p[1] << 4;
    b[2] = p[2] << 4;
    b[3] = p[3] << 4;
    FUN_001a1f98(b);
}
