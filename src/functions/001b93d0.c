// FUNCTION: SLPM 0x001B93D0  size 48  core 44
// *(char*)(p+0x98) = v; if (*(int*)(p+4) != 0) FUN_001b3c60(*(int*)(p+4));  (tail sibcall)
extern void FUN_001b3c60(int);

void FUN_001b93d0(char *p, char v)
{
    *(char *)(p + 0x98) = v;
    if (*(int *)(p + 4) != 0)
        FUN_001b3c60(*(int *)(p + 4));
}
