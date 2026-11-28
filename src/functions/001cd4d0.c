// FUNCTION: SLPM 0x001CD4D0  size 72  core 72
extern char D_00241EB0[];
extern void FUN_001cffc0(int a0);

void FUN_001cd4d0(char *p)
{
    if (*(int *)(p + 232) != 0)
        (*(void (**)(void))D_00241EB0)();
    FUN_001cffc0(*(int *)(p + 8));
    *(int *)(p + 4) = 0;
}
