// FUNCTION: SLPM 0x001CC308  size 48 core 44
extern int D_00241E78;

void FUN_001cc308(char *p)
{
    int v = *(int *)(p + 0xC0);

    if (v != 0)
        ((void (*)(int))D_00241E78)(v);
}
