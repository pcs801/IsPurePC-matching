extern int FUN_001e9090();
extern void FUN_00112260(int);

void FUN_00111de8(char *p)
{
    *(int *)p = 3;
    FUN_00112260(0);
    *(int *)(p + 0x50) = (FUN_001e9090(1, 0x80E0, 1, 2, 0, 0) & 0xFFFFFF) - *(int *)(p + 0x44);
    FUN_001e9090(1, 0x80D0, 1, 0, *(int *)(p + 0x58), 0x4000, 0x800);
    *(int *)(p + 0x00) = 0;
    *(int *)(p + 0x2C) = 0;
    *(int *)(p + 0x34) = 0;
    *(int *)(p + 0x38) = 0;
    *(int *)(p + 0x40) = 0;
    *(int *)(p + 0x54) = 0;
    *(int *)(p + 0x4C) = 0;
    *(int *)(p + 0x50) = 0;
}