// FUNCTION: SLPM 0x001CC4F0  size 48 core 44
extern int D_00241E84;

void FUN_001cc4f0(char *p)
{
    int v = *(int *)(p + 0xB4);

    if (v != 0)
        ((void (*)(int))D_00241E84)(v);
}
