// FUNCTION: SLPM 0x001137C8  size 88 (core 84)
extern void FUN_001f6118(void);
extern void FUN_0020dd90(int h);
extern void FUN_0020af08(int h);

int FUN_001137c8(int *obj)
{
    if (*(int *)obj) {
        FUN_001f6118();
        FUN_0020dd90(*(int *)((char *)obj + 0x2C));
    } else {
        FUN_0020af08(*(int *)((char *)obj + 0x30));
    }
    return 1;
}
