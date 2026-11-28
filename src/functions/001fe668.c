extern int FUN_00202e38(int a0);

int FUN_001fe668(int a0, int a1)
{
    if (*(int *)(a1 + 8) != 0) {
        FUN_00202e38(a0);
        *(int *)(a1 + 4) = 0;
        return 1;
    }
    *(int *)(a1 + 4) = 0;
    return 0;
}
