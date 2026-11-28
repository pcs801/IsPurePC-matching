extern void FUN_0013ede8(void);

int FUN_0013eda8(char *p)
{
    if (*(short *)(p + 0x10) == 0) {
        FUN_0013ede8();
        *(short *)(p + 0x10) = 1;
    }
    return 0;
}
