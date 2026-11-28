extern int D_00865C48[];
extern char D_008659A0[];

void FUN_001cbba8(void)
{
    if (D_00865C48[0] != 0)
        ((void (*)(int))D_00865C48[0])(D_00865C48[1]);
}

char *FUN_001cbbd8(void)
{
    return D_008659A0;
}
