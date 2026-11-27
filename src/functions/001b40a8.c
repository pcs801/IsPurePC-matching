// SLPM 0x001B40A8 slice (core 52) holds three tiny accessors:
//   0x1B40A8 return *(int*)(p+0xA8)
//   0x1B40B0 D_0022F418 = v
//   0x1B40C0 D_0022F41C = 40 - v; D_0022F420 = v
extern int D_0022F418;
extern int D_0022F41C;
extern int D_0022F420;

int FUN_001b40a8(char *p)
{
    return *(int *)(p + 0xA8);
}

void FUN_001b40b0(int v)
{
    D_0022F418 = v;
}

void FUN_001b40c0(int v)
{
    D_0022F41C = 40 - v;
    D_0022F420 = v;
}
