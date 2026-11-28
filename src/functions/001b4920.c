// FUNCTION: SLPM 0x001B4920  size 48
void FUN_001b4920(char *p)
{
    int v = *(int *)(p + 0x18);

    *(int *)(p + 0x38) = 0;
    *(int *)(p + 0x50) = 0;
    *(char *)(p + 1) = (char)((v == 0) ? 3 : 2);
    *(char *)(p + 2) = 0;
    *(int *)(p + 0x28) = 0;
    *(int *)(p + 0x2C) = 0;
    *(char *)(p + 0x4B) = 1;
}
