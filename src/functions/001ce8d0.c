extern void FUN_001ce6c8(char *p);
extern void FUN_001ce530(char *p);
extern void FUN_001ce3b8(char *p);

void FUN_001ce8d0(char *p)
{
    short v = *(short *)(p + 0x9C);

    if (v == 2)
        FUN_001ce6c8(p);
    else if (v == 1)
        FUN_001ce530(p);
    else if (v == 0)
        FUN_001ce3b8(p);
}
