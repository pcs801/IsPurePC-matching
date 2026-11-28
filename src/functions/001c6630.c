// FUNCTION: SLPM 0x001c6630  size 80  core 80 (two functions in one symbol)
extern int D_00238870;
extern int D_00238868;

void FUN_001c6630(char *p, unsigned int a1)
{
    if (D_00238870 == 1 && D_00238868 <= 0)
        return;
    if (a1 >= 2)
        return;
    if (*(signed char *)(p + 0x56) == a1)
        return;
    *(char *)(p + 1) = *(unsigned char *)(p + 0x56);
    *(signed char *)(p + 0x56) = a1;
}

int FUN_001c6678(char *p)
{
    return *(signed char *)(p + 0x57);
}
