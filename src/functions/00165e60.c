// FUNCTION: SLPM 0x00165E60  size 88  core 88
extern char *D_002709A8[];
extern int FUN_001a82a8(void *a0);

int FUN_00165e60(void)
{
    int i;

    for (i = 0; i < 6; i++) {
        if (FUN_001a82a8(*(int *)D_002709A8 + i * 20 + 108) == 0)
            return 0;
    }
    return 1;
}
