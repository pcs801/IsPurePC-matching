// FUNCTION: SLPM 0x001EAB38  size 32  core 32
extern void FUN_001f3dc8(char *);
int FUN_001eab38(char *p)
{
    do {
        FUN_001f3dc8((char *)(*(int *)(p + 0x40)) + 0x68);
    } while (0);
    return 1;
}
