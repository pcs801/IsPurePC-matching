// FUNCTION: SLPM 0x001BBE38  size 48  core 44
// s0 = p; FUN_001d0cb0(*(int*)p); *(char*)(p+9) = 0;
extern void FUN_001d0cb0(int);

void FUN_001bbe38(char *p)
{
    FUN_001d0cb0(*(int *)p);
    *(char *)(p + 9) = 0;
}
