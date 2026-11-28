extern void FUN_001cffe8(int a0);

void FUN_001cd518(char *p)
{
    if (*(int *)(p + 4) == 3) {
        FUN_001cffe8(*(int *)(p + 8));
        *(int *)(p + 0x8C) = 0;
        *(int *)(p + 4) = 0;
    }
}
