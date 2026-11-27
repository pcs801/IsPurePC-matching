// SLPM 0x001CD180 slice (core 40) holds THREE tiny getters:
//   0x001CD180 -> p ? *(int*)(p+0x2C) : 0
//   0x001CD198 -> *(int*)(p+0x30)
//   0x001CD1A0 -> *(int*)(p+0x34)
int FUN_001cd180(char *p)
{
    if (p == 0)
        return 0;
    return *(int *)(p + 0x2C);
}

int FUN_001cd198(char *p)
{
    return *(int *)(p + 0x30);
}

int FUN_001cd1a0(char *p)
{
    return *(int *)(p + 0x34);
}
