extern void FUN_001d1230(int a0);

void FUN_001bc2f8(char *p)
{
    FUN_001d1230(*(int *)p);
}

void FUN_001bc310(char *p, int v)
{
    *(int *)(p + 0x2C) = v;
}

void FUN_001bc318(char *p)
{
    *(int *)(p + 0xC) = 1;
}
