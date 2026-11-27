// SLPM 0x001CD0E8 slice (core 112) holds THREE functions:
//   0x1CD0E8 state getter: v = *(s16*)(p+0x98); v==0 -> 16; v==2 -> (w==2 ? 4 : (w^1 ? 16 : 8));
//            v==1 -> (w^2 ? 16 : 4); else 16   where w = *(s16*)(p+0x9C)
//   0x1CD148 return *(int*)(p+0x10)
//   0x1CD150 return *(signed char*)(p+0xF)
// Status: 112/112 bytes, 20 words off (branch layout / constant scheduling).
int FUN_001cd0e8(char *p)
{
    short v = *(short *)(p + 0x98);
    short w;

    if (v == 0)
        return 16;
    if (v != 2) {
        if (v != 1)
            return 16;
        w = *(short *)(p + 0x9C);
        return (w ^ 2) ? 16 : 4;
    }
    w = *(short *)(p + 0x9C);
    if (w == 2)
        return 4;
    return (w ^ 1) ? 16 : 8;
}

int FUN_001cd148(char *p)
{
    return *(int *)(p + 0x10);
}

int FUN_001cd150(char *p)
{
    return *(signed char *)(p + 0xF);
}
