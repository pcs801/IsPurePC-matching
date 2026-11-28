extern int FUN_001ea268(int a0);
extern int FUN_001ea138(int a0);

void FUN_001ea810(int a0)
{
    if (*(int *)(*(int *)(a0 + 0x40) + 0x184) == 3)
        FUN_001ea268(a0);
    else
        FUN_001ea138(a0);
}
