extern char D_00865C30[];
extern int FUN_001cae08(int a0);

void FUN_001cb6a8(int a0, int a1)
{
    FUN_001cae08(a0);
    *(int *)(D_00865C30 + 4) = a1;
    *(int *)(D_00865C30) = a0;
}
