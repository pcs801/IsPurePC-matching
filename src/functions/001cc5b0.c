extern int D_00241E8C;

void FUN_001cc5b0(int a0)
{
    int v;

    v = *(int *)(a0 + 0xB4);
    if (v == 0)
        return;
    ((void (*)(int))D_00241E8C)(v);
}

int FUN_001cc5e0(void)
{
    return 0;
}
