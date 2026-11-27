// FUNCTION: SLPM 0x001EAB60  size 32  core 32
extern void FUN_001f3eb0(char *);

int FUN_001eab60(char *p)
{
    FUN_001f3eb0((char *)(*(int *)(p + 0x40)) + 0x68);
    return 1;
}
