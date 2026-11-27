// FUNCTION: SLPM 0x00111C80  size 64  core 60
extern void FUN_001121f8(int);
extern void FUN_0020dd90(int);

int FUN_00111c80(char *p)
{
    FUN_001121f8(0);
    FUN_0020dd90(*(int *)(p + 0x44));
    FUN_0020dd90(*(int *)(p + 0x58));
    return 1;
}
