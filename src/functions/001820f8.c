// FUNCTION: SLPM 0x001820F8  size 40  core 36
extern void FUN_00181c88(int, int);

int FUN_001820f8(char *obj)
{
    FUN_00181c88(*(int *)(obj + 0x44), 0x80);
    return 0;
}
