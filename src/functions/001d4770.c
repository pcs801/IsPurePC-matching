extern void FUN_001d45c8(char *p);
extern void FUN_001d4448(char *p);
extern void FUN_001d42b0(char *p);

void FUN_001d4770(char *p)
{
    short v = *(short *)(p + 0x9C);

    if (v == 2)
        FUN_001d45c8(p);
    else if (v == 1)
        FUN_001d4448(p);
    else
        FUN_001d42b0(p);
}
