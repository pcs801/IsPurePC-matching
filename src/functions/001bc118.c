extern void FUN_001bbec8(char *p);
extern void FUN_001bbe68(char *p);

void FUN_001bc118(char *p)
{
    signed char v = *(signed char *)(p + 9);

    if (v == 2)
        FUN_001bbec8(p);
    else if (v == 1)
        FUN_001bbe68(p);
}
